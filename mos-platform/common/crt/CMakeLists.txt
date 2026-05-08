# libcrt is the libcalls needed by the compiler. All libcalls emitted by the
# compiler (except C standard library functions) should be here.
add_platform_library(common-crt
  const.S

  call-indir.S

  divmod.cc
  divmod-large.cc
  mul.cc
  shift.cc
  rotate.cc
)

# Merge the builtins library from llvm-mos into libcrt.
# Query clang for its resource directory
execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-resource-dir
  RESULT_VARIABLE CLANG_RESOURCE_RESULT
  OUTPUT_VARIABLE CLANG_RESOURCE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT CLANG_RESOURCE_RESULT EQUAL 0)
  message(FATAL_ERROR
    "Failed to run ${CMAKE_C_COMPILER} -print-resource-dir")
endif()

set(BUILTINS_DIR
  ${CLANG_RESOURCE_DIR}/lib/mos-unknown-unknown)

if(NOT EXISTS "${BUILTINS_DIR}")
  message(FATAL_ERROR
    "Builtins directory not found: ${BUILTINS_DIR}")
endif()

find_library(builtins clang_rt.builtins REQUIRED
  PATHS ${BUILTINS_DIR}
  NO_DEFAULT_PATH
)

merge_libraries(common-crt ${builtins})
