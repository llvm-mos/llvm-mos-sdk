cmake_minimum_required(VERSION 3.18)

project(test-nes-cnrom LANGUAGES C)

include(../test.cmake)

add_mesen_test(minimal)
add_mesen_test(chr-ram)
add_mesen_test(chr-rom)
add_mesen_test(chr-swap-split)

add_subdirectory(no-compile)
