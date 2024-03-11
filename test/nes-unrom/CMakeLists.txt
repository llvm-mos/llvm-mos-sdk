cmake_minimum_required(VERSION 3.18)

project(test-nes-unrom LANGUAGES C)

include(../test.cmake)

add_nes_test(minimal)
add_nes_test(prg-rom-256)
add_nes_test(prg-rom-banked-call)
