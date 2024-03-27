platform(lynx PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  _mikey.h
  _suzy.h
  lynx.h
TYPE INCLUDE)

add_platform_library(lynx-crt0)
merge_libraries(lynx-crt0
  common-copy-zp-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(lynx-c)
target_include_directories(lynx-c SYSTEM BEFORE PUBLIC .)
target_link_libraries(lynx-c PRIVATE common-asminc)
