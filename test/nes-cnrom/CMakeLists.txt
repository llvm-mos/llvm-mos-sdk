cmake_minimum_required(VERSION 3.18)

project(test-nes-cnrom LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)
add_nes_test(chr-ram)
add_nes_test(chr-rom)
add_nes_test(chr-swap-split)

add_subdirectory(no-compile)
