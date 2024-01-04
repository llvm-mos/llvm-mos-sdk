platform(rpc8e COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

# crt0 build code

add_platform_object_file(rpc8e-crt0-o crt0.o crt0.S)

add_platform_library(rpc8e-crt0 init-stack.S)
merge_libraries(rpc8e-crt0
  common-copy-zp-data
  common-zero-bss
  common-exit-loop
)
target_link_libraries(rpc8e-crt0-o PRIVATE common-asminc)
target_link_libraries(rpc8e-crt0 PRIVATE common-asminc)
target_compile_options(rpc8e-crt0-o PUBLIC -mcpu=mos65el02)
target_compile_options(rpc8e-crt0 PUBLIC -mcpu=mos65el02)

# librpc8e build code

add_platform_library(rpc8e-c
  librpc8e/src/abort.c
  librpc8e/src/display.c
  librpc8e/src/drive.c
  librpc8e/src/mmu.c
  librpc8e/src/sortron.c
)
target_include_directories(rpc8e-c SYSTEM BEFORE PUBLIC librpc8e/include)
target_compile_options(rpc8e-c PUBLIC -mcpu=mos65el02)

install(DIRECTORY librpc8e/include/rpc8e TYPE INCLUDE)
install(FILES librpc8e/include/rpc8e.h TYPE INCLUDE)
