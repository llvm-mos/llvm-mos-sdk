cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)

add_nes_test(chr-ram)
add_nes_test(chr-rom)

add_nes_test(prg-rom-16)
add_nes_test(prg-rom-32)

add_nes_test(prg-ram)
add_nes_test(prg-ram-c)
target_link_options(prg-ram-c.nes PRIVATE -Tcommon.ld -Tc-in-prg-ram.ld)

add_nes_test(zp-data)

add_nes_test(prg-rom-dpcm)
add_nes_test(prg-rom-dpcm-pad)

add_subdirectory(no-compile)
