platform(commodore PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cbm.h
  chrout.h
TYPE INCLUDE)
install(FILES cbm_kernal.inc DESTINATION ${ASMINCDIR})
install(FILES commodore.ld TYPE LIB)

add_platform_library(commodore-crt0)
merge_libraries(commodore-crt0
  common-init-stack
  common-copy-zp-data
  common-zero-bss
  common-exit-return
)

add_platform_library(commodore-c
  abort.c
  chrout.c
  getchar.c
  putchar.c
  cbm_k_acptr.c
  cbm_k_basin.c
  cbm_k_bsout.c
  cbm_k_chkin.s
  cbm_k_chrin.c
  cbm_k_chrout.c
  cbm_k_ciout.c 
  cbm_k_ckout.c
  cbm_k_clall.c
  cbm_k_close.c
  cbm_k_clrch.c
  cbm_k_getin.c
  cbm_k_iobase.s
  cbm_k_listen.c
  cbm_k_load.s
  cbm_k_open.s
  cbm_k_readst.c
  cbm_k_save.s
  cbm_k_scnkey.c
  cbm_k_second.c
  cbm_k_setlfs.s
  cbm_k_setnam.s
  cbm_k_talk.c
  cbm_k_tksa.c
  cbm_k_udtim.c
  cbm_k_unlsn.c
  cbm_k_untlk.c
)

# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily. It can also be called in an interrupt.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)
target_include_directories(commodore-c BEFORE PUBLIC .)
target_link_libraries(commodore-c PRIVATE common-asminc)
