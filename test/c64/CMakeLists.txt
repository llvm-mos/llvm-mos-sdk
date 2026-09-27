cmake_minimum_required(VERSION 3.18)

project(test-c64 LANGUAGES C CXX)

include(../test.cmake)

set(VICE_EMULATOR ${VICE_X64SC_COMMAND})
set(VICE_LIBRETRO_CORE ${LIBRETRO_VICE_X64SC_CORE})

# Exit path in a program that is large (exit() in the range where BASIC's ROM
# reappears, $A000 and up): finishes and reports, and hands control back to
# BASIC.
add_vice_test(exit-large)
add_vice_basic_return_test(basic-return)
add_vice_basic_return_test(basic-return-large)
