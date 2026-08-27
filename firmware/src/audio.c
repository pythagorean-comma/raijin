/*
 * audio.c -- plays flash-resident mono PCM out of an I2S DAC/amp.
 *
 * Data path:
 *
 *   const int16_t clip[] in .rodata     memory-mapped XIP flash; nothing is
 *        |                              copied to RAM at boot
 *        |  CPU, inside the DMA completion IRQ:
 *        |  mono -> stereo, volume, 5 ms edge fades
 *        v
 *   two uint32_t ping-pong buffers      2 KiB of RAM total
 *        |  DMA, paced by the PIO TX DREQ
 *        v
 *   PIO state machine -> BCLK / LRCLK / DIN -> MAX98357A
 *
 * The CPU only ever touches 256 frames at a time, roughly every 11.6 ms at
 * 22.05 kHz, so playback costs a small fraction of one core.
 */

#include "audio.h"

#include <string.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "i2s.pio.h"

#define AUDIO_BUF_FRAMES 256                          /* ~11.6 ms at 22.05 kHz */
#define FADE_SAMPLES     (CLIP_SAMPLE_RATE / 200u)    /* 5 ms click guard      */
#define TAIL_BUFFERS     2                            /* silence flushed after */

static uint32_t buf[2][AUDIO_BUF_FRAMES];
static int      dma_ch;
static PIO      pio = pio0;
static uint     pio_sm;

static const int16_t *src_samples;
static uint32_t       src_length;
static uint32_t       src_pos;
static int            tail;            /* <0: source still running; else silence left */
static volatile int   play_idx;
static volatile bool  ready[2];
static volatile bool  playing;
static uint16_t       volume_q8 = 256;

/* Read one buffer's worth straight out of flash. Returns false on the buffer
 * that contains the end of the clip (the remainder is zero-padded). */
static bool fill(uint32_t *dst) {
    uint32_t pos = src_pos;
    for (uint i = 0; i < AUDIO_BUF_FRAMES; i++) {
        int32_t s = 0;
        if (pos < src_length) {
            s = src_samples[pos];

            /* Linear ramps at both ends: without them the step from silence to
             * the first sample is an audible click through a class-D amp. */
            uint32_t remain = src_length - pos;
            if (pos < FADE_SAMPLES) {
                s = s * (int32_t)pos / (int32_t)FADE_SAMPLES;
            } else if (remain < FADE_SAMPLES) {
                s = s * (int32_t)remain / (int32_t)FADE_SAMPLES;
            }

            s = (s * (int32_t)volume_q8) >> 8;
            if (s >  32767) s =  32767;
            if (s < -32768) s = -32768;
            pos++;
        }
        /* One mono sample duplicated into both I2S channels:
         * (left << 16) | (right & 0xffff) */
        uint32_t u = (uint16_t)(int16_t)s;
        dst[i] = (u << 16) | u;
    }
    src_pos = pos;
    return pos < src_length;
}

/* Stage the next buffer. Returns false when there is nothing left to queue. */
static bool prepare(int idx) {
    if (tail < 0) {
        if (!fill(buf[idx])) tail = TAIL_BUFFERS;
        return true;
    }
    if (tail > 0) {
        memset(buf[idx], 0, sizeof buf[idx]);
        tail--;
        return true;
    }
    return false;
}

static void start_buffer(int idx) {
    dma_channel_set_trans_count(dma_ch, AUDIO_BUF_FRAMES, false);
    dma_channel_set_read_addr(dma_ch, buf[idx], true);   /* true = trigger */
}

static void __isr dma_handler(void) {
    dma_hw->ints0 = 1u << dma_ch;
    if (!playing) return;

    int next = play_idx ^ 1;
    if (!ready[next]) {                 /* clip finished; leave the DMA stopped */
        playing = false;
        return;
    }

    /* Re-arm first -- the 8-entry PIO FIFO gives ~360 us of slack at 22.05 kHz,
     * so this comfortably beats the underrun deadline. Refill afterwards. */
    start_buffer(next);
    play_idx    = next;
    ready[next] = false;

    ready[next ^ 1] = prepare(next ^ 1);
}

void audio_init(void) {
#if AUDIO_PIN_AMP_SD >= 0
    gpio_init(AUDIO_PIN_AMP_SD);
    gpio_set_dir(AUDIO_PIN_AMP_SD, GPIO_OUT);
    gpio_put(AUDIO_PIN_AMP_SD, 0);      /* amp held in shutdown until we play */
#endif

    uint offset = pio_add_program(pio, &i2s_out_program);
    pio_sm = pio_claim_unused_sm(pio, true);
    i2s_out_program_init(pio, pio_sm, offset,
                         AUDIO_PIN_DIN, AUDIO_PIN_BCLK, CLIP_SAMPLE_RATE);

    dma_ch = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_ch);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, pio_get_dreq(pio, pio_sm, true));
    dma_channel_configure(dma_ch, &c, &pio->txf[pio_sm],
                          buf[0], AUDIO_BUF_FRAMES, false);

    dma_channel_set_irq0_enabled(dma_ch, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

void audio_set_volume(uint16_t vol_q8) { volume_q8 = vol_q8; }

void audio_play(const audio_clip_t *clip) {
    audio_wait();

    src_samples = clip->samples;
    src_length  = clip->length;
    src_pos     = 0;
    tail        = -1;

    ready[0] = prepare(0);
    ready[1] = prepare(1);

#if AUDIO_PIN_AMP_SD >= 0
    gpio_put(AUDIO_PIN_AMP_SD, 1);      /* un-mute before the first sample */
    sleep_ms(5);                        /* MAX98357A start-up time */
#endif

    play_idx = 0;
    ready[0] = false;
    playing  = true;
    start_buffer(0);
}

bool audio_is_playing(void) { return playing; }

void audio_wait(void) {
    while (playing) tight_loop_contents();

    dma_channel_abort(dma_ch);
    dma_hw->ints0 = 1u << dma_ch;

#if AUDIO_PIN_AMP_SD >= 0
    gpio_put(AUDIO_PIN_AMP_SD, 0);      /* mute: kills the idle hiss between clips */
#endif
}
