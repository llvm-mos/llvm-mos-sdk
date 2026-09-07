platform(lynx-lnx COMPLETE PARENT lynx)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  link.ld
  bootldr.ld
  directory.ld
TYPE LIB)

# Add LNX file header to crt0 so it's always linked
add_platform_object_file(lynx-lnx-crt0-o
  crt0.o)

add_platform_library(lynx-lnx-crt0)

# Merge in the parent lynx crt0
merge_libraries(lynx-lnx-crt0
  lynx-crt0)

target_link_libraries(lynx-lnx-crt0-o PUBLIC lynx-lnx-crt0)
