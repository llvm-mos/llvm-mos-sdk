cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc3 LANGUAGES C)

include(../test.cmake)

add_nes_test(banked-8)
add_nes_test(banked-8-64k)
add_nes_test(banked-8-128k)
add_nes_test(banked-8-256k)
add_nes_test(banked-mode-0)
target_link_options(banked-mode-0.nes PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-banked-mode-0.ld)
add_nes_test(banked-mode-1)
target_link_options(banked-mode-1.nes PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-banked-mode-1.ld)
add_nes_test(fixed)
target_link_options(fixed.nes PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-fixed.ld)
add_nes_test(minimal)

add_subdirectory(no-compile)
