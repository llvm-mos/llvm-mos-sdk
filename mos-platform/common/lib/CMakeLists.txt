# Common targets cannot be directly created since they have to be specialized
# per-platform. This file defines functions that platforms use to create these
# targets according to a common template. Each platform has the opportunity
# to add additional sources or exclude common ones through variadic args.

function(_add_common_target name)
  cmake_parse_arguments(ARG "" "" "COMMON_SOURCES;PLATFORM_SOURCES;EXCLUDE_COMMON_SOURCES" ${ARGN})
  if(NOT LLVM_MOS_CURRENT_PLATFORM)
    message(FATAL_ERROR "llvm_mos_sdk_add_${name}() can only be used in llvm_mos_sdk_add_platform() scope")
  endif()
  set(target_name ${LLVM_MOS_CURRENT_PLATFORM}-${name})
  # TODO: When CMake 3.17 is more widespread, this hard-coded path can be
  # replaced with CMAKE_CURRENT_FUNCTION_LIST_DIR.
  set(source_dir ${CMAKE_SOURCE_DIR}/mos-platform/common/lib)
  if(${ARG_EXCLUDE_COMMON_SOURCES})
    list(REMOVE_ITEM ARG_COMMON_SOURCES ${ARG_EXCLUDE_COMMON_SOURCES})
  endif()
  list(TRANSFORM ARG_COMMON_SOURCES PREPEND ${source_dir}/)
  add_library(${target_name} STATIC ${ARG_COMMON_SOURCES} ${ARG_PLATFORM_SOURCES})
  set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${name})
  llvm_mos_sdk_install(TARGETS ${target_name})
  llvm_mos_sdk_track_platform_target(${target_name})
endfunction()

# Specializes start target for the current platform named <platform>-start.
# Additional arguments add source files to the target.
# EXCLUDE_COMMON_SOURCES excludes common source files from the target.
#
# libstart is a collection of initialization and finalization routines that may
# or may not be needed by a given program. These are basically the optional
# portions of crt0.o.
function(llvm_mos_sdk_add_start)
  _add_common_target(start
    COMMON_SOURCES
      zero_bss.c

      init_array.c
      fini_array.c

      exit_return.c

    PLATFORM_SOURCES
      ${ARGN}
  )

  # TODO: When CMake 3.17 is more widespread, this hard-coded path can be
  # replaced with CMAKE_CURRENT_FUNCTION_LIST_DIR.
  set(source_dir ${CMAKE_SOURCE_DIR}/mos-platform/common/lib)

  target_compile_options(${LLVM_MOS_CURRENT_PLATFORM}-start PRIVATE -fno-lto)
endfunction()

# Specializes crt target for the current platform named <platform>-crt.
# Additional arguments add source files to the target.
# EXCLUDE_COMMON_SOURCES excludes common source files from the target.
function(llvm_mos_sdk_add_crt)
  _add_common_target(crt
    COMMON_SOURCES
      const.S

      call_indir.S

      divmod.cc
      divmod_large.cc
      mul.cc
      shift.cc

    PLATFORM_SOURCES
      ${ARGN}
  )

  # TODO: When CMake 3.17 is more widespread, this hard-coded path can be
  # replaced with CMAKE_CURRENT_FUNCTION_LIST_DIR.
  set(source_dir ${CMAKE_SOURCE_DIR}/mos-platform/common/lib)

  # Don't pull in stack pointer init unnecessarily.
  set_property(
    SOURCE
      ${source_dir}/divmod_large.cc
    PROPERTY COMPILE_FLAGS -fno-lto
  )
endfunction()

# Specializes c target for the current platform named <platform>-c.
# Additional arguments add source files to the target.
# EXCLUDE_COMMON_SOURCES excludes common source files from the target.
function(llvm_mos_sdk_add_c)
  _add_common_target(c
    COMMON_SOURCES
      # ctype.h
      ctype.c

      # setjmp.h
      setjmp.S

      # stdio.h
      printf.c
      stdio.c

      # stdlib.h
      abs.cc
      exit.c
      stdlib.cc
      new.cc

      # string.h
      mem.c
      string.c

      # exception
      exception.cc

      # Itanium ABI implementation
      cxa_abi.cc
      cxa_atexit.cc
      private_typeinfo.cpp

    PLATFORM_SOURCES
      ${ARGN}
  )

  # TODO: When CMake 3.17 is more widespread, this hard-coded path can be
  # replaced with CMAKE_CURRENT_FUNCTION_LIST_DIR.
  set(source_dir ${CMAKE_SOURCE_DIR}/mos-platform/common/lib)

  # Prevent the implementation of libcalls from being reduced to a call of those libcalls.
  set_property(SOURCE ${source_dir}/mem.c
    PROPERTY COMPILE_FLAGS -fno-builtin-memset
  )
  set_property(SOURCE ${source_dir}/printf.c
    PROPERTY COMPILE_DEFINITIONS
    PRINTF_DISABLE_SUPPORT_FLOAT
    PRINTF_DISABLE_SUPPORT_EXPONENTIAL
  )
endfunction()

# Specializes m target for the current platform named <platform>-m.
# Additional arguments add source files to the target.
# EXCLUDE_COMMON_SOURCES excludes common source files from the target.
function(llvm_mos_sdk_add_m)
  _add_common_target(m
    COMMON_SOURCES
      stub.c
    PLATFORM_SOURCES
      ${ARGN}
  )
endfunction()
