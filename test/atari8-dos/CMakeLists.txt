cmake_minimum_required(VERSION 3.18)

project(test-atari8-dos LANGUAGES C)

include(../test.cmake)

add_subdirectory(compile)
add_subdirectory(no-compile)
