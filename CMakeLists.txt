cmake_minimum_required(VERSION 3.10)

project(llvm-mos-sdk LANGUAGES C ASM)

set(CMAKE_ASM_COMPILER_TARGET mos)

include_directories(.)

add_subdirectory(c64)
