cmake_minimum_required(VERSION 3.10)

project(llvm-mos-sdk LANGUAGES C CXX ASM)

if (NOT DEFINED LLVM_MOS)
message(FATAL_ERROR "LLVM_MOS must be set to the LLVM binary directory.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Place all binaries in {build}/bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(common)
add_subdirectory(commodore)
add_subdirectory(atari)
add_subdirectory(sim)
