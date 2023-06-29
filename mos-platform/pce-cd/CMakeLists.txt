platform(pce-cd PARENT pce-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  binary-cd.ld
  binary-scd.ld
  ipl.ld
  ipl-ram.ld
  cd-memory.ld
  cd-sections.ld
  cd-ram-banked-sections.ld
  ipl-cd-ram-banked-sections.ld
  scd-ram-banked-sections.ld
  link.ld
TYPE LIB)

include_directories(BEFORE SYSTEM .)

# crt0 build code

add_platform_library(pce-cd-crt0
  crt0/copy-zp-data.S
  crt0/zero-zp-bss.S
)
merge_libraries(pce-cd-crt0
  common-init-stack
  common-exit-loop
)

target_link_libraries(pce-cd-crt0 PRIVATE common-asminc)
target_compile_options(pce-cd-crt0 PUBLIC -mcpu=moshuc6280)

# libpce extensions build code

# add_platform_library(pce-cd-c)

# target_include_directories(pce-cd-c SYSTEM BEFORE PUBLIC libpce/include)
# target_compile_options(pce-cd-c PUBLIC -mcpu=moshuc6280)
# target_link_libraries(pce-cd-c PRIVATE common-asminc)

# install(DIRECTORY libpce/include/pce TYPE INCLUDE)
# install(FILES libpce/include/pce-cd.h TYPE INCLUDE)

