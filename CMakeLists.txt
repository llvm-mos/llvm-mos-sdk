cmake_minimum_required(VERSION 3.18)

# MinSizeRel is the preferred default for building the SDK.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to MinSizeRel")
  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type (default MinSizeRel)" FORCE)
endif()

project(llvm-mos-sdk LANGUAGES C CXX ASM)

include(ExternalProject)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option(LLVM_MOS_BUILD_EXAMPLES "Build examples for all supported platforms." On)

if(NOT CMAKE_CROSSCOMPILING)
  # Fetch LLVM-MOS for the host and install it into the prefix.
  include(find-mos-compiler)
  find_mos_compiler(LLVM_MOS_C_COMPILER mos-clang)
  find_mos_compiler(LLVM_MOS_CXX_COMPILER mos-clang++)
  find_mos_compiler(LLVM_MOS_ASM_COMPILER mos-clang)
  set(bootstrap_compiler Off)
  if(NOT LLVM_MOS_BOOTSTRAP_COMPILER AND
     LLVM_MOS_C_COMPILER AND LLVM_MOS_CXX_COMPILER AND LLVM_MOS_ASM_COMPILER)
    message(STATUS "Found MOS compiler: ${LLVM_MOS_C_COMPILER}")
  else()
    message(STATUS "Did not find MOS compiler - Enabling bootstrap download.")
    set(bootstrap_compiler On)
  endif()
  option(LLVM_MOS_BOOTSTRAP_COMPILER
         "Should I download a working LLVM-MOS compiler for use with this SDK?"
         ${bootstrap_compiler})
  include(bootstrap-compiler)
  if(LLVM_MOS_BOOTSTRAP_COMPILER AND llvm-mos_SOURCE_DIR)
    unset(LLVM_MOS_C_COMPILER)
    unset(LLVM_MOS_CXX_COMPILER)
    unset(LLVM_MOS_ASM_COMPILER)
    set(LLVM_MOS ${llvm-mos_SOURCE_DIR})
    find_mos_compiler(LLVM_MOS_C_COMPILER mos-clang)
    find_mos_compiler(LLVM_MOS_CXX_COMPILER mos-clang++)
    find_mos_compiler(LLVM_MOS_ASM_COMPILER mos-clang)
    if(LLVM_MOS_C_COMPILER AND LLVM_MOS_CXX_COMPILER AND LLVM_MOS_ASM_COMPILER)
      message(STATUS "Found MOS compiler: ${LLVM_MOS_C_COMPILER}")
      install(DIRECTORY ${llvm-mos_SOURCE_DIR}/ DESTINATION . USE_SOURCE_PERMISSIONS)
    else()
      message(FATAL_ERROR "Downloaded llvm-mos is not usable.")
    endif()
  endif()

  find_program(MESEN_COMMAND NAMES mesen Mesen.exe ENV MESEN_DIR)
  message(STATUS "Mesen NES emulator: ${MESEN_COMMAND}")

  find_program(EMUTEST_COMMAND NAMES emutest emutest.exe
    PATHS ENV EMUTEST_DIR)
  message(STATUS "Emutest test runner: ${EMUTEST_COMMAND}")

  find_library(LIBRETRO_STELLA_CORE
    NAMES stella2014_libretro.so stella2014_libretro.dylib stella2014_libretro.dll
    PATHS /lib64/libretro ENV LIBRETRO_CORES_DIR)
  message(STATUS "Libretro Stella core: ${LIBRETRO_STELLA_CORE}")

  find_library(LIBRETRO_NESTOPIA_CORE
    NAMES nestopia_libretro.so nestopia_libretro.dylib nestopia_libretro.dll
    PATHS /lib64/libretro ENV LIBRETRO_CORES_DIR)
  message(STATUS "Libretro Nestopia core: ${LIBRETRO_NESTOPIA_CORE}")

  find_library(LIBRETRO_FCEUMM_CORE
    NAMES fceumm_libretro.so fceumm_libretro.dylib fceumm_libretro.dll
    PATHS /lib64/libretro ENV LIBRETRO_CORES_DIR)
  message(STATUS "Libretro FCEUMM core: ${LIBRETRO_FCEUMM_CORE}")

  # Install toolchain and config file for users of find_package(llvm-mos-sdk).
  # CMake's find_package logic will discover
  # `$PATH/../lib/cmake/llvm-mos-sdk/llvm-mos-sdk-config.cmake` which in turn
  # sets the toolchain file. The project command will then have all information
  # to set up the llvm-mos compiler.
  install(FILES
          cmake/llvm-mos-toolchain.cmake
          cmake/llvm-mos-sdk-config.cmake
          cmake/find-mos-compiler.cmake
          DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

  # Install example files.
  install(DIRECTORY ${CMAKE_SOURCE_DIR}/examples DESTINATION .)

  add_subdirectory(utils)
endif()

add_subdirectory(mos-platform)

if(NOT CMAKE_CROSSCOMPILING)
  add_subdirectory(test)
endif()
