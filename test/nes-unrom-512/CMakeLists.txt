cmake_minimum_required(VERSION 3.18)

project(test-nes-unrom-512 LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)
add_nes_test(prg-rom-512)
add_nes_test(prg-rom-banked-call)
add_nes_test(chr-ram)
add_fceumm_test(chr-rom)
add_fceumm_test(chr-swap-split)

add_subdirectory(no-compile)
