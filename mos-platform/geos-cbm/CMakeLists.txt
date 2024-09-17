platform(geos-cbm COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES geos.h geos_constants.h geos_symbols.h geos_memorymap.h geos_types.h geos_routines.h TYPE INCLUDE)
install(FILES geos.ld vlir.ld link.ld TYPE LIB)

add_platform_library(geos-cbm-crt crt0.c geos_crt.c)

merge_libraries(geos-cbm-crt 
	common-crt0 
	common-init-stack 
	common-copy-zp-data 
	common-zero-bss
)

target_include_directories(geos-cbm-crt BEFORE PUBLIC .)
target_link_libraries(geos-cbm-crt PUBLIC common-asminc)
