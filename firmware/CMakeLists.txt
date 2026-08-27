cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2_w CACHE STRING "Board type")
set(PICO_PLATFORM rp2350 CACHE STRING "Platform")

include(pico_sdk_import.cmake)
project(pico2w_audio C CXX ASM)
set(CMAKE_C_STANDARD 11)
pico_sdk_init()

# ---------------------------------------------------------------------------
# Audio clips: every .wav in audio/ is converted at build time into a raw PCM
# blob plus a generated clips.S that .incbin's it into .rodata (i.e. flash).
# Drop a new .wav in the folder and rebuild -- nothing else to edit.
# ---------------------------------------------------------------------------
set(AUDIO_RATE 22050 CACHE STRING "Playback sample rate in Hz")

file(GLOB CLIP_WAVS CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/audio/*.wav)
set(GEN ${CMAKE_CURRENT_BINARY_DIR}/generated)

add_custom_command(
    OUTPUT ${GEN}/clips.h ${GEN}/clips.c ${GEN}/clips.S
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN}
    COMMAND python3
            ${CMAKE_CURRENT_LIST_DIR}/tools/wav2flash.py
            --rate ${AUDIO_RATE}
            --normalize -3
            --outdir ${GEN}
            ${CLIP_WAVS}
    DEPENDS ${CLIP_WAVS} ${CMAKE_CURRENT_LIST_DIR}/tools/wav2flash.py
    COMMENT "Converting WAV clips to flash-resident PCM at ${AUDIO_RATE} Hz"
    VERBATIM
)

add_executable(firmware
    src/main.c
    src/audio.c
    ${GEN}/clips.c
    ${GEN}/clips.S
)

pico_generate_pio_header(firmware ${CMAKE_CURRENT_LIST_DIR}/src/i2s.pio)

target_include_directories(firmware PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src ${GEN})
target_link_libraries(firmware pico_stdlib hardware_pio hardware_dma)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 0)
pico_add_extra_outputs(firmware)
