cmake_minimum_required(VERSION 3.18)

project(test-nes-unrom LANGUAGES C)

include(../test.cmake)

add_mesen_test(minimal)
add_mesen_test(prg-rom-256)
