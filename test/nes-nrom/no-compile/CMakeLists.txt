cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1-nocompile LANGUAGES C)

add_executable(chr-rom-too-big chr-rom-too-big.c)
add_executable(chr-rom-non-pow2 chr-rom-non-pow2.c)
add_executable(chr-ram-too-big chr-ram-too-big.c)

add_executable(prg-rom-too-big prg-rom-too-big.c)
add_executable(prg-ram-too-big prg-ram-too-big.c)
