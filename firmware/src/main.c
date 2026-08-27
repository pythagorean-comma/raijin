/*
 * main.c -- boot, then cycle: play a clip, idle, repeat.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "audio.h"

#define IDLE_MS 30000       /* gap between clips */

int main(void) {
    stdio_init_all();
    audio_init();
    audio_set_volume(200);          /* ~78% of unity */

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
