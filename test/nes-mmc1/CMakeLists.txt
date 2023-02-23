cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)

include(../test.cmake)

add_mesen_test(minimal)

add_mesen_test(chr-ram)
add_mesen_test(chr-rom)

add_mesen_test(prg-rom-16-fixed)
target_link_options(prg-rom-16-fixed PRIVATE -Tcommon.ld -Tprg-rom-fixed.ld -Tc-in-ram.ld)

add_mesen_test(prg-rom-32-fixed)
target_link_options(prg-rom-32-fixed PRIVATE -Tcommon.ld -Tprg-rom-fixed.ld -Tc-in-ram.ld)

add_mesen_test(prg-rom-32)
target_link_options(prg-rom-32 PRIVATE -Tcommon.ld -Tprg-rom-32.ld -Tc-in-ram.ld)

add_mesen_test(prg-rom-64)
target_link_options(prg-rom-64 PRIVATE -Tcommon.ld -Tprg-rom-64.ld -Tc-in-ram.ld)

add_mesen_test(prg-rom-128)
target_link_options(prg-rom-128 PRIVATE -Tcommon.ld -Tprg-rom-128.ld -Tc-in-ram.ld)

add_mesen_test(prg-rom-256)

add_mesen_test(prg-ram)

add_mesen_test(prg-ram-c)
target_link_options(prg-ram-c PRIVATE -Tcommon.ld -Tprg-rom-128.ld -Tc-in-prg-ram-0.ld)

add_subdirectory(no-compile)
