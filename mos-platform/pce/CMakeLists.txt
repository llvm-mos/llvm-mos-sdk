platform(pce COMPLETE PARENT pce-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _rom-banked-sections.ld
  rom-sections.ld
TYPE LIB)

include_directories(BEFORE SYSTEM .)

# crt0 build code

add_platform_object_file(pce-crt0-o crt0.o crt0/crt0.S)

add_platform_library(pce-crt0
  crt0/copy-data.S
  crt0/copy-zp-data.S
  crt0/irq.S
  crt0/zero-bss.S
  crt0/zero-zp-bss.S
)
merge_libraries(pce-crt0
  common-init-stack
  common-exit-loop
)

target_link_libraries(pce-crt0-o PRIVATE common-asminc)
target_link_libraries(pce-crt0 PRIVATE common-asminc)
target_compile_options(pce-crt0-o PUBLIC -mcpu=moshuc6280)
target_compile_options(pce-crt0 PUBLIC -mcpu=moshuc6280)
