cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)

include(../test.cmake)

add_mesen_test(minimal)

add_mesen_test(chr-ram)
add_mesen_test(chr-rom)

add_mesen_test(prg-rom-16)
add_mesen_test(prg-rom-32)

add_mesen_test(prg-ram)
add_mesen_test(prg-ram-c)
target_link_options(prg-ram-c PRIVATE -Tcommon.ld -Tc-in-prg-ram.ld)

add_mesen_test(zp-data)

add_subdirectory(no-compile)
