platform(dodo COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES api.h TYPE INCLUDE)

add_platform_object_file(dodo-crt0-o crt0.o crt0.s)
target_link_libraries(dodo-crt0-o PRIVATE common-asminc)

add_platform_library(dodo-crt0)
merge_libraries(dodo-crt0
  common-copy-zp-data
  common-zero-bss
  common-init-stack
  common-exit-loop
)

add_platform_library(dodo-c api.s)
target_link_libraries(dodo-c PRIVATE common-asminc)

target_include_directories(dodo-c SYSTEM BEFORE PUBLIC .)
target_compile_options(dodo-c PUBLIC -mcpu=mos65c02)
