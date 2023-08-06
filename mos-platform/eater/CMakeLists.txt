platform(eater PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES eater.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(eater-crt0
  crt0/delay.c
  crt0/reset.S
  crt0/serial.S
  crt0/systick.S
)
merge_libraries(eater-crt0
  common-crt0
  common-init-stack
  common-copy-zp-data
  common-zero-bss
  common-exit-loop
)

target_compile_options(eater-crt0 PUBLIC -mcpu=mosw65c02)
target_link_libraries(eater-crt0 PRIVATE common-asminc)
