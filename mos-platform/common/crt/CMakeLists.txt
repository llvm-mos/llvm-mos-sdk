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
# Don't pull in stack pointer init unnecessarily.
# This can be called in an interrupt.
set_property(SOURCE divmod-large.cc PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)

# Merge the builtins library from llvm-mos into libcrt.
get_filename_component(compiler_dir ${CMAKE_C_COMPILER} DIRECTORY)
find_library(builtins clang_rt.builtins REQUIRED PATHS ${compiler_dir}/../lib/clang/18/lib/mos-unknown-unknown NO_DEFAULT_PATH)
merge_libraries(common-crt ${builtins})
