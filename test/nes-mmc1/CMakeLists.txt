cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)

add_nes_test(chr-ram)
add_nes_test(chr-rom)

add_nes_test(prg-rom-16-fixed)
target_link_options(prg-rom-16-fixed.nes PRIVATE -Tcommon.ld -Tprg-rom-fixed.ld -Tc-in-ram.ld)

add_nes_test(prg-rom-32-fixed)
target_link_options(prg-rom-32-fixed.nes PRIVATE -Tcommon.ld -Tprg-rom-fixed.ld -Tc-in-ram.ld)

add_nes_test(prg-rom-32)
add_nes_test(prg-rom-64)
add_nes_test(prg-rom-128)
add_nes_test(prg-rom-256)

add_nes_test(prg-ram)

add_nes_test(prg-ram-c)
target_link_options(prg-ram-c.nes PRIVATE -Tcommon.ld -Tprg-rom-banked.ld -Tc-in-prg-ram-0.ld)

add_subdirectory(no-compile)
