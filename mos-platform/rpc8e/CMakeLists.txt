platform(rpc8e COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

# crt0 build code

function(add_platform_65el02_object_file target output)
  _check_platform()
  _check_cross_compiling(YES)
  _check_target_prefix(${target})

  if(ARGN)
    add_library(${target} STATIC ${ARGN})
  else()
    add_library(${target} STATIC ${CMAKE_SOURCE_DIR}/mos-platform/stub.c)
  endif()

  get_filename_component(compiler_dir ${CMAKE_C_COMPILER} DIRECTORY)
  find_program(LLVM_MOS_LINKER ld.lld HINTS ${compiler_dir} REQUIRED)

  add_custom_command(OUTPUT ${output}
    COMMAND ${LLVM_MOS_LINKER} -r -o ${output} --whole-archive -mllvm -mcpu=mos65el02
            $<TARGET_FILE:${target}>)
  add_custom_target(${target}-o ALL DEPENDS ${output})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${output} TYPE LIB)

  _merge_parent_library(${target})
endfunction()

add_platform_65el02_object_file(rpc8e-crt0-o crt0.o crt0.c)

add_platform_library(rpc8e-crt0)
merge_libraries(rpc8e-crt0
  common-copy-zp-data
  common-zero-bss
  common-exit-loop
)
target_compile_options(rpc8e-crt0 PUBLIC -mcpu=mos65el02 -fno-static-stack)

# librpc8e build code

add_platform_library(rpc8e-c
  librpc8e/src/abort.c
  librpc8e/src/display.c
  librpc8e/src/drive.c
  librpc8e/src/mmu.c
  librpc8e/src/sortron.c
)
target_include_directories(rpc8e-c SYSTEM BEFORE PUBLIC librpc8e/include)
target_compile_options(rpc8e-c PUBLIC -mcpu=mos65el02 -fno-static-stack)

# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE librpc8e/src/abort.c PROPERTY COMPILE_FLAGS -fno-lto)

install(DIRECTORY librpc8e/include/rpc8e TYPE INCLUDE)
install(FILES librpc8e/include/rpc8e.h TYPE INCLUDE)
