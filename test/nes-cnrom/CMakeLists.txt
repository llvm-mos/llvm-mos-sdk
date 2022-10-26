cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)

include(../test.cmake)

add_mesen_test(minimal)
add_mesen_test(chr-ram)
add_mesen_test(chr-rom)

add_subdirectory(no-compile)
