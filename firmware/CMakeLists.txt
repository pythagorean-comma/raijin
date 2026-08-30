# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2_w CACHE STRING "Board type")
set(PICO_PLATFORM rp2350 CACHE STRING "Platform")

include(pico_sdk_import.cmake)
project(raijin_firmware C CXX ASM)
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

add_executable(raijin_firmware
    src/main.c
    src/audio.c
    ${GEN}/clips.c
    ${GEN}/clips.S
)

pico_generate_pio_header(raijin_firmware ${CMAKE_CURRENT_LIST_DIR}/src/i2s.pio)

target_include_directories(raijin_firmware PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src ${GEN})
target_link_libraries(raijin_firmware pico_stdlib hardware_pio hardware_dma)

pico_enable_stdio_usb(raijin_firmware 1)
pico_enable_stdio_uart(raijin_firmware 0)
pico_add_extra_outputs(raijin_firmware)
