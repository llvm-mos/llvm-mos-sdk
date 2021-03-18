cmake_minimum_required(VERSION 3.10)

project(llvm-mos-sdk LANGUAGES C ASM)

if (NOT DEFINED LLVM_MOS)
message(FATAL_ERROR "LLVM-MOS must be set to the LLVM binary directory.")
endif()
set(CMAKE_ASM_COMPILER "${LLVM_MOS}/clang")
set(CMAKE_ASM_FLAGS "--target=mos")

include_directories(.)

add_subdirectory(commodore/64)
