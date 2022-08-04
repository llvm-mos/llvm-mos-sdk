include(merge-libraries)

function(_check_platform)
  if(NOT PLATFORM)
    message(FATAL_ERROR "platform() was not called in the current scope.")
  endif()
endfunction()

function(_check_cross_compiling value)
  if(CMAKE_CROSSCOMPILING AND NOT value)
    message(FATAL_ERROR "Host-only function called in target build.")
  endif()
  if(NOT CMAKE_CROSSCOMPILING AND value)
    message(FATAL_ERROR "Target-only function called in host build.")
  endif()
endfunction()

function(_check_target_prefix target)
  if(NOT ${target} MATCHES ^${PLATFORM}-)
    message(FATAL_ERROR "Expected target to start with '${PLATFORM}-'; got '${target}'")
  endif()
endfunction()

# Declare a target platform, possibly with the given PARENT platform.  The other
# add_platform_xxx calls require this to have been called in a containing scope.
#
# If the platform is declared COMPLETE, then the platform is capable of
# producing complete binaries; accordingly, a "link.ld" linker script must be
# present. A HOSTED platform supports the fragment of the C standard library
# currently implemented. A COMPLETE platform cannot have any descendants.
function(platform name)
  cmake_parse_arguments(ARGS "COMPLETE;HOSTED" PARENT "" ${ARGN})

  set(PLATFORM ${name})
  set(PLATFORM ${name} PARENT_SCOPE)
  set(PARENT ${ARGS_PARENT})
  set(PARENT ${ARGS_PARENT} PARENT_SCOPE)
  set(COMPLETE ${ARGS_COMPLETE})
  set(COMPLETE ${ARGS_COMPLETE} PARENT_SCOPE)
  set(HOSTED ${ARGS_HOSTED})
  set(HOSTED ${ARGS_HOSTED} PARENT_SCOPE)

  set(CMAKE_INSTALL_LIBDIR mos-platform/${PLATFORM}/lib)
  set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} PARENT_SCOPE)
  set(CMAKE_INSTALL_INCLUDEDIR mos-platform/${PLATFORM}/include)
  set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} PARENT_SCOPE)
  set(ASMINCDIR mos-platform/${PLATFORM}/asminc PARENT_SCOPE)

  include(GNUInstallDirs)

  if(NOT CMAKE_CROSSCOMPILING)
    # Clang searches for config files next to itself as a last resort.  If the
    # --config flag is not set, argv0 of the form <config>-clang sets the implicit
    # config file as <config>.cfg. We leverage this convention using a set of
    # symlinks for each MOS platform.
    foreach(suffix clang clang++ clang-cpp)
      if(WIN32)
        install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/install-clang-batch-file.cmake
                CODE "install_clang_batch_file(${CMAKE_INSTALL_FULL_BINDIR} ${PLATFORM} ${suffix})")
      else()
        install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/install-clang-symlink.cmake
                CODE "install_clang_symlink(${CMAKE_INSTALL_FULL_BINDIR} ${PLATFORM} ${suffix})")
      endif()
    endforeach()

    if(COMPLETE)
      _add_platform_examples(${PLATFORM}-examples)
    endif()
    return()
  endif()

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/clang.cfg)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/clang.cfg CONFIG)
  endif()

  # Add Clang configuration file.
  set(clang_config ${CMAKE_CURRENT_BINARY_DIR}/mos-${PLATFORM}.cfg)
  if(PARENT)
    configure_file(${CMAKE_SOURCE_DIR}/mos-platform/derived.cfg ${clang_config})
  else()
    configure_file(${CMAKE_SOURCE_DIR}/mos-platform/root.cfg ${clang_config})
  endif()
  install(FILES ${clang_config} TYPE BIN)

  if(COMPLETE)
    install(FILES link.ld TYPE LIB)
  endif()
endfunction()

# Add a static library to the current platform. The target name must begin with
# the name of the current platform, followed by a dash. The output name of the
# library has this prefix removed.
function(add_platform_library target)
  _check_platform()
  _check_cross_compiling(YES)
  _check_target_prefix(${target})

  if(ARGN)
    add_library(${target} STATIC ${ARGN})
  else()
    add_library(${target} STATIC ${CMAKE_SOURCE_DIR}/mos-platform/stub.c)
  endif()

  string(REGEX REPLACE ^${PLATFORM}- "" output_name ${target})
  set_property(TARGET ${target} PROPERTY OUTPUT_NAME ${output_name})
  install(TARGETS ${target})

  _merge_parent_library(${target})
endfunction()

# Add an object file to the current platform. The target is nominally a static
# library; the output is produced by relocatably linking together all files
# in the library.
function(add_platform_object_file target output)
  _check_platform()
  _check_cross_compiling(YES)
  _check_target_prefix(${target})

  if(ARGN)
    add_library(${target} STATIC ${ARGN})
  else()
    add_library(${target} STATIC ${CMAKE_SOURCE_DIR}/mos-platform/stub.c)
  endif()

  add_custom_command(OUTPUT ${output}
    COMMAND ${CMAKE_LINKER} -r -o ${output} --whole-archive
            $<TARGET_FILE:${target}>)
  add_custom_target(${target}-o ALL DEPENDS ${output})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${output} TYPE LIB)

  _merge_parent_library(${target})
endfunction()

# Build the example project against the current platform.
function(_add_platform_examples target)
  _check_platform()
  _check_cross_compiling(NO)
  _check_target_prefix(${target})

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
      -DHOSTED=${HOSTED}
      -DCMAKE_C_FLAGS=${config_flag}
      -DCMAKE_CXX_FLAGS=${config_flag}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
    BUILD_ALWAYS On
    EXCLUDE_FROM_ALL ${exclude_from_all}
    DEPENDS mos-platform)
endfunction()

# Merge the library of the same name (sans the platform prefix) in the parent
# platform into the given target. If there is no parent or corresponding
# library, does nothing.
function(_merge_parent_library target)
  if(PARENT)
    string(REGEX REPLACE ^${PLATFORM} ${PARENT} parent_target ${target})
    if(TARGET ${parent_target})
      merge_libraries(${target} ${parent_target})
    endif()
  endif()
endfunction()
