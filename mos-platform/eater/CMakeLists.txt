platform(eater COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  chrin.h
  eater.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(eater-crt0
  crt0/reset.S
  crt0/serial.S
  crt0/systick.S
)
merge_libraries(eater-crt0
  common-crt0
  common-init-stack
  common-copy-data
  common-zero-bss
  common-exit-loop
)

add_platform_library(eater-c
  delay.c
  getchar.c
  lcd.c
  putchar.c
)

target_compile_options(eater-crt0 PUBLIC -mcpu=mosw65c02)
target_link_libraries(eater-crt0 PRIVATE common-asminc)

target_include_directories(eater-c BEFORE PUBLIC .)
target_compile_options(eater-c PUBLIC -mcpu=mosw65c02)
target_link_libraries(eater-c PRIVATE common-asminc)
