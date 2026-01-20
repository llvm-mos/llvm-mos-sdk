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
get_filename_component(compiler_dir ${CMAKE_C_COMPILER} DIRECTORY)
file(GLOB builtins_dir ${compiler_dir}/../lib/clang/*/lib/mos-unknown-unknown)
list(LENGTH builtins_dir num_builtins_dirs)
if(NOT num_builtins_dirs EQUAL 1)
  message(FATAL_ERROR "Found ${num_builtins_dirs} builtin dirs; expected 1")
endif()
find_library(builtins clang_rt.builtins REQUIRED PATHS ${builtins_dir} NO_DEFAULT_PATH)
merge_libraries(common-crt ${builtins})
