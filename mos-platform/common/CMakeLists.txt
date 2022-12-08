platform(common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(DIRECTORY ${INCLUDE_DIR}/ TYPE INCLUDE)

# Math library; just a stub for now.
add_platform_library(common-m)

add_subdirectory(asminc)
add_subdirectory(crt0)
add_subdirectory(crt)
add_subdirectory(c)

add_subdirectory(ldscripts)
