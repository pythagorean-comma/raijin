/*
 * main.c -- the stimulus loop: a 500 ms flash and noise burst together, then a
 * dark, silent wait, repeated for as long as the device is switched on. One
 * burst starts a random 2-6 s after the last one did.
 *
 * The timing is taken from Mr FlashyBeepy, an Arduino build of the training
 * device described in Rowland, Bushnell, Duncan and Stein, "Ameliorating
 * Hemianopia with Multisensory Training", J. Neurosci. 43(6):1018-1026 (2023).
 * https://github.com/Watty-Git/mrflashybeepy
 *
 * Their loop, reduced to its timing:
 *
 *     int interval = random(2000, 6000);
 *     led on;  play("burst.wav");  delay(500);  pause();  led off;
 *     delay(interval);
 *
 * with one deliberate difference. Their delay runs after the burst, so their
 * 2-6 s is the off time and their bursts land 2.5-6.5 s apart. The paper and
 * their own README both describe the interval between stimuli as 2-6 s, so the
 * burst is subtracted from the wait here and the interval is the 2-6 s.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/rand.h"
#include "audio.h"

#define BURST_MS        500     /* flash and noise together, per the protocol   */
#define INTERVAL_MIN_MS 2000    /* burst onset to burst onset ...               */
#define INTERVAL_MAX_MS 6000    /* ... uniform over [MIN, MAX), which leaves a  */
                                /*     dark, silent 1500-5499 ms in between     */

/* Bench aid for debugging the LED wiring; audio stays muted throughout.
 *   0 = normal operation
 *   1 = hold the strips on
 *   2 = square-wave the LED pins, 3 s high then 3 s low, for probing the driver */
#define LED_DEBUG 0

/* audio/ holds the single 500 ms burst, so the generated clip table has one
 * entry. Dropping more WAVs in would build fine but only the first is used. */
_Static_assert(CLIP_COUNT >= 1, "audio/ must contain at least one WAV");

/* The loop waits INTERVAL - BURST_MS, so the burst has to fit inside the
 * shortest interval or that subtraction wraps. */
_Static_assert(INTERVAL_MIN_MS > BURST_MS, "the burst must fit in the interval");

/* Arduino's random(min, max) is uniform over [min, max-1]; this matches it.
 * get_rand_32() seeds and stirs a PRNG from whatever entropy the chip offers --
 * the hardware TRNG on the RP2350, the ring oscillator and a RAM hash on an
 * RP2040 -- so the sequence differs on every power-up either way. There is no
 * analogRead(A0) seeding trick to copy across, and none is needed. */
static uint32_t interval_ms(void) {
    return INTERVAL_MIN_MS + get_rand_32() % (INTERVAL_MAX_MS - INTERVAL_MIN_MS);
}

int main(void) {
    stdio_init_all();
    audio_init();
    audio_set_volume(200);          /* ~78% of unity */

#if LED_DEBUG && AUDIO_LED_PINS
    /* audio_init() has already left the amp muted, so none of this makes a sound. */
#if LED_DEBUG == 2
    printf("LED debug: square wave on the LED pins, 3 s high / 3 s low\n");
    while (true) {
        audio_leds(true);
        printf("channels high\n");
        sleep_ms(3000);
        audio_leds(false);
        printf("channels low\n");
        sleep_ms(3000);
    }
#else
    printf("LED debug: strips held on\n");
    audio_leds(true);
    while (true) tight_loop_contents();
#endif
#endif

    const audio_clip_t *burst = &audio_clips[0];
    printf("burst clip %s (%lu samples, %.2f s), flash %u ms, interval %u-%u ms\n",
           burst->name, (unsigned long)burst->length,
           (double)burst->length / CLIP_SAMPLE_RATE,
           BURST_MS, INTERVAL_MIN_MS, INTERVAL_MAX_MS - 1);

    /* The 5 ms amp settle in audio_play() and the two buffers of tail silence
     * that audio_wait() drains sit outside the flash window, so each cycle runs
     * about 28 ms longer than the interval drawn here. */
    while (true) {
        audio_play(burst);          /* returns as the first sample is clocked out */
        audio_leds(true);           /* so light and sound start together */
        sleep_ms(BURST_MS);
        audio_leds(false);
        audio_wait();               /* mutes the amp once the clip has drained */

        uint32_t interval = interval_ms();
        printf("burst; interval %lu ms\n", (unsigned long)interval);
        sleep_ms(interval - BURST_MS);
    }
}
