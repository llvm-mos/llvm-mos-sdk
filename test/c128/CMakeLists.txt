cmake_minimum_required(VERSION 3.18)

project(test-c128 LANGUAGES C CXX ASM)

include(../test.cmake)

set(VICE_EMULATOR ${VICE_X128_COMMAND})
set(VICE_LIBRETRO_CORE ${LIBRETRO_VICE_X128_CORE})

# Exit path in a program that is large (exit() above $4000): finishes and
# reports, and hands control back to BASIC.
add_vice_test(exit-large)
add_vice_basic_return_test(basic-return)
add_vice_basic_return_test(basic-return-large)
