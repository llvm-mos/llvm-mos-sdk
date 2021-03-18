cmake_minimum_required(VERSION 3.10)

project(llvm-mos-sdk LANGUAGES C ASM)

if (NOT DEFINED LLVM_MOS)
message(FATAL_ERROR "LLVM-MOS must be set to the LLVM binary directory.")
endif()

set(CMAKE_ASM_COMPILER "${LLVM_MOS}/clang")
set(CMAKE_C_COMPILER "${LLVM_MOS}/clang")
set(CMAKE_AR "${LLVM_MOS}/llvm-ar")
set(CMAKE_RANLIB "${LLVM_MOS}/llvm-ranlib")

set(CMAKE_ASM_FLAGS "--target=mos")
set(CMAKE_C_FLAGS "--target=mos -flto -Os")

include_directories(.)

add_subdirectory(commodore/64)
