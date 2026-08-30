/*
 * main.c -- boot, then cycle: play a clip, idle, repeat.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "audio.h"

#define IDLE_MS 30000       /* gap between clips */

/* Bench aid while the LED wiring is debugged; audio stays muted throughout.
 *   0 = normal operation
 *   1 = hold the strips on
 *   2 = square-wave the LED pins, 3 s high then 3 s low, for probing the module */
#define LED_DEBUG 2

int main(void) {
    stdio_init_all();
    audio_init();
    audio_set_volume(200);          /* ~78% of unity */

#if LED_DEBUG && AUDIO_LED_PINS
    /* audio_init() has already left the amp muted, so none of this makes a sound. */
#if LED_DEBUG == 2
    printf("LED debug: GP20/21/22 square wave, 3 s high / 3 s low\n");
    while (true) {
        gpio_set_mask(AUDIO_LED_PINS);
        printf("channels high\n");
        sleep_ms(3000);
        gpio_clr_mask(AUDIO_LED_PINS);
        printf("channels low\n");
        sleep_ms(3000);
    }
#else
    printf("LED debug: strips held on\n");
    gpio_set_mask(AUDIO_LED_PINS);
    while (true) tight_loop_contents();
#endif
#endif

    uint32_t n = 0;
    while (true) {
        const audio_clip_t *clip = &audio_clips[n++ % CLIP_COUNT];
        printf("playing %s (%lu samples, %.2f s)\n",
               clip->name, (unsigned long)clip->length,
               (double)clip->length / CLIP_SAMPLE_RATE);

        audio_play(clip);
        audio_wait();               /* blocks; also mutes the amp when done */

        sleep_ms(IDLE_MS);
    }
}
