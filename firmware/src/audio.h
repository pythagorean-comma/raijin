#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "clips.h"

/* Pin map -- change to match your board.
 * BCLK and LRCLK must be adjacent GPIOs, in that order (PIO side-set). */
#ifndef AUDIO_PIN_BCLK
#define AUDIO_PIN_BCLK   16      /* LRCLK is implicitly AUDIO_PIN_BCLK + 1 */
#endif
#ifndef AUDIO_PIN_DIN
#define AUDIO_PIN_DIN    18
#endif
#ifndef AUDIO_PIN_AMP_SD
#define AUDIO_PIN_AMP_SD 19      /* MAX98357A SD_MODE; -1 to disable */
#endif
/* MOSFET driver input -- GP22, switching all three LED strips together for the
 * length of a clip. A mask, so more pins can be added. Set to 0 to disable. */
#ifndef AUDIO_LED_PINS
#define AUDIO_LED_PINS   (1u << 22)
#endif

void audio_init(void);

/* Start a clip. Returns immediately -- playback runs on DMA + PIO. */
void audio_play(const audio_clip_t *clip);

/* True while a clip is still being clocked out. */
bool audio_is_playing(void);

/* Block until the current clip has finished (and the amp has been muted). */
void audio_wait(void);

/* 0..256, applied while filling the DMA buffers. 256 = unity. */
void audio_set_volume(uint16_t vol_q8);
