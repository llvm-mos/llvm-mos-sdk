cmake_minimum_required(VERSION 3.18)

project(test-nes-gtrom LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)
add_nes_test(prg-rom-512)
add_nes_test(prg-rom-banked-call)
add_nes_test(chr-ram)
add_nes_test(prg-rom-dpcm)

# emulators have trouble with the GTROM 111 mapper using CHR ROM
add_mesen_mono_test(chr-rom)
add_mesen_mono_test(chr-swap-split)

add_subdirectory(no-compile)
