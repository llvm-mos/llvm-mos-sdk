include(install-symlink)
include(object-file)

function(_check_platform)
  if(NOT PLATFORM)
    message(FATAL_ERROR "platform() was not called in the current scope.")
  endif()
endfunction()

function(_check_target_prefix target)
  if(NOT ${target} MATCHES ^${PLATFORM}-)
    message(FATAL_ERROR "Expected target to start with '${PLATFORM}-'; got '${target}'")
  endif()
endfunction()

function(install_clang_symlinks)
endfunction()

# Declare a target platform, possibly with the given parent platform. This sets
# the PLATFORM and PARENT variables accordingly, sets up install directories,
# and generates a Clang configuration file and corresponding symlinks. The other
# add_platform_xxx calls require this to have been called in a containing scope.
function(platform name)
  cmake_parse_arguments(ARGS "" PARENT "" ${ARGN})

  set(PLATFORM ${name})
  set(PLATFORM ${name} PARENT_SCOPE)
  set(PARENT ${ARGS_PARENT})
  set(PARENT ${ARGS_PARENT} PARENT_SCOPE)

  if(NOT CMAKE_CROSSCOMPILING)
    # Clang searches for config files next to itself as a last resort.  If the
    # --config flag is not set, argv0 of the form <config>-clang sets the implicit
    # config file as <config>.cfg. We leverage this convention using a set of
    # symlinks for each MOS platform.
    foreach(suffix clang clang++ clang-cpp)
      install_symlink(mos-${PLATFORM}-${suffix} mos-${suffix})
    endforeach()
    return()
  endif()

  set(CMAKE_INSTALL_LIBDIR mos-platform/${PLATFORM}/lib PARENT_SCOPE)
  set(CMAKE_INSTALL_INCLUDEDIR mos-platform/${PLATFORM}/include PARENT_SCOPE)

  # Add Clang configuration file.
  set(clang_config ${CMAKE_CURRENT_BINARY_DIR}/mos-${PLATFORM}.cfg)
  if(PARENT)
    configure_file(${CMAKE_SOURCE_DIR}/mos-platform/derived.cfg ${clang_config})
  else()
    configure_file(${CMAKE_SOURCE_DIR}/mos-platform/root.cfg ${clang_config})
  endif()
  install(FILES ${clang_config} TYPE BIN)
endfunction()

# Add a static library to the current platform. The target name must begin with
# the name of the current platform, followed by a dash. The output name of the
# library has this prefix removed.
function(add_platform_library target)
  _check_platform()
  _check_target_prefix(${target})

  if(ARGN)
    add_library(${target} STATIC ${ARGN})
  else()
    add_library(${target} STATIC ${CMAKE_SOURCE_DIR}/mos-platform/stub.c)
  endif()

  string(REGEX REPLACE ^${PLATFORM}- "" output_name ${target})
  set_property(TARGET ${target} PROPERTY OUTPUT_NAME ${output_name})
  install(TARGETS ${target})
endfunction()

# Add an object file to the current platform. The target is nominally a static
# library; the output is produced by relocatably linking together all files
# in the library.
function(add_platform_object_file target output)
  _check_platform()
  _check_target_prefix(${target})

  if(ARGN)
    add_library(${target} STATIC ${ARGN})
  else()
    add_library(${target} STATIC ${CMAKE_SOURCE_DIR}/mos-platform/stub.c)
  endif()
  generate_object_file(${target} ${output})
  install_object_files(${target})
endfunction()

# Build the example project against the current platform. Any arguments provided
# are passed as <ARG>=YES flags to the underlying project's CMake configuration
# step. See the example project for the semantics of various options.
function(add_platform_examples target)
  _check_platform()
  _check_target_prefix(${target})

  foreach(prop ${ARGN})
    list(APPEND prop_args -D${prop}=YES)
  endforeach()

  get_filename_component(llvm_mos ${LLVM_MOS_C_COMPILER} DIRECTORY)

  if(LLVM_MOS_BUILD_EXAMPLES)
    set(exclude_from_all NO)
  else()
    set(exclude_from_all YES)
  endif()

  ExternalProject_Get_Property(mos-platform INSTALL_DIR)
  set(config_flag "--config ${INSTALL_DIR}/bin/mos-${PLATFORM}.cfg")

  ExternalProject_Add(${target}
    SOURCE_DIR   ${CMAKE_SOURCE_DIR}/examples
    INSTALL_DIR  ${CMAKE_BINARY_DIR}/examples/${PLATFORM}
    BINARY_DIR   ${CMAKE_BINARY_DIR}/examples/${PLATFORM}/build
    STAMP_DIR    ${CMAKE_BINARY_DIR}/examples/${PLATFORM}/build/stamp
    TMP_DIR      ${CMAKE_BINARY_DIR}/examples/${PLATFORM}/build/tmp
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/examples/${PLATFORM}/build
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
      -DLLVM_MOS=${llvm_mos}
      -DPLATFORM=${PLATFORM}
      -DCMAKE_C_FLAGS=${config_flag}
      -DCMAKE_CXX_FLAGS=${config_flag}
      ${prop_args}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
    BUILD_ALWAYS On
    EXCLUDE_FROM_ALL ${exclude_from_all}
    DEPENDS mos-platform)
endfunction()
