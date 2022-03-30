cmake_minimum_required(VERSION 3.18)

# CMake should consider MOS as an embedded platform with no OS assumptions.
set(CMAKE_SYSTEM_NAME Generic)

# By default, MOS is targeted generically with no platform config files.
set(compiler_prefix mos)
if(LLVM_MOS_PLATFORM)
  # When using a prefix with both llvm-mos and llvm-mos-sdk installed,
  # platforms are specified simply by prefixing the compiler path accordingly.
  # Clang's internal logic is able to find the installed config files and use
  # those without any further flags set by CMake.
  set(compiler_prefix mos-${LLVM_MOS_PLATFORM})
else()
  # CMake cannot link test programs if there is not a specific platform set.
  # Skip ABI and feature checks if this is the case.
  set(CMAKE_C_COMPILER_FORCED On)
  set(CMAKE_CXX_COMPILER_FORCED On)
endif()

# Find mos compilers if not already set.
include(${CMAKE_CURRENT_LIST_DIR}/find-mos-compiler.cmake)
find_mos_compiler(CMAKE_C_COMPILER ${compiler_prefix}-clang)
find_mos_compiler(CMAKE_CXX_COMPILER ${compiler_prefix}-clang++)
find_mos_compiler(CMAKE_ASM_COMPILER ${compiler_prefix}-clang)
if(NOT CMAKE_C_COMPILER OR NOT CMAKE_CXX_COMPILER OR NOT CMAKE_ASM_COMPILER)
  message(FATAL_ERROR "Did not find LLVM-MOS compiler.")
endif()

get_filename_component(compiler_dir ${CMAKE_C_COMPILER} DIRECTORY)
find_program(CMAKE_AR llvm-ar HINTS ${compiler_dir} REQUIRED)
find_program(CMAKE_RANLIB llvm-ranlib HINTS ${compiler_dir} REQUIRED)
set(CMAKE_C_COMPILER_AR ${CMAKE_AR} CACHE FILEPATH "")
set(CMAKE_CXX_COMPILER_AR ${CMAKE_AR} CACHE FILEPATH "")
set(CMAKE_C_COMPILER_RANLIB ${CMAKE_RANLIB} CACHE FILEPATH "")
set(CMAKE_CXX_COMPILER_RANLIB ${CMAKE_RANLIB} CACHE FILEPATH "")

# MinSizeRel is the preferred default for MOS.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to MinSizeRel")
  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type (default MinSizeRel)" FORCE)
endif()
