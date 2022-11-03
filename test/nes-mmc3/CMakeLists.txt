cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc3 LANGUAGES C)

include(../test.cmake)

add_mesen_test(banked-8)
add_mesen_test(banked-mode-0)
target_link_options(banked-mode-0 PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-banked-mode-0.ld)
add_mesen_test(fixed)
target_link_options(fixed PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-fixed.ld)
add_mesen_test(minimal)

add_subdirectory(no-compile)
