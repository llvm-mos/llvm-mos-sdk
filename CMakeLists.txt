cmake_minimum_required(VERSION 3.15)

# MinSizeRel is the preferred default for building the SDK.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to MinSizeRel")
  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type (default MinSizeRel)" FORCE)
endif()

project(llvm-mos-sdk LANGUAGES C CXX ASM)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option(LLVM_MOS_BUILD_EXAMPLES "Build examples for all supported platforms." On)

include(sdk-support)
add_subdirectory(mos-platform)

if(NOT MOS)
  add_subdirectory(utils)

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

  # Make nested build directory targeting MOS (which will have MOS=On)
  include(ExternalProject)
  ExternalProject_Add(mos-build
    SOURCE_DIR
      ${CMAKE_SOURCE_DIR}
    BINARY_DIR
      ${CMAKE_BINARY_DIR}/mos-build
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
      -DLLVM_MOS_BUILD_EXAMPLES=${LLVM_MOS_BUILD_EXAMPLES}
      -DCMAKE_C_COMPILER=${LLVM_MOS_C_COMPILER}
      -DCMAKE_CXX_COMPILER=${LLVM_MOS_CXX_COMPILER}
      -DCMAKE_ASM_COMPILER=${LLVM_MOS_ASM_COMPILER}
      -DCMAKE_C_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_CXX_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_ASM_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_MAXIMUM_RECURSION_DEPTH=400
    INSTALL_COMMAND ""
    BUILD_ALWAYS On
    USES_TERMINAL_BUILD On)

  # Clean the mos-build directory with the host project.
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
    ADDITIONAL_CLEAN_FILES "${CMAKE_BINARY_DIR}/mos-build")

  # Have the host project trigger the mos installation.
  # ExternalProject wants to install even if we're just building.
  install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build . --target install
                                WORKING_DIRECTORY \"${CMAKE_BINARY_DIR}/mos-build\")")

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
endif()
