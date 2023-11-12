cmake_minimum_required(VERSION 3.18)

project(test-atari2600-3e LANGUAGES C)

include(../atari2600-common/test.cmake)

add_vcs_test(xram ../atari2600-common)

add_vcs_test(code-bank .)
