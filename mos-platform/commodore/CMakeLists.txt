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
  cbm_k_acptr.s
  cbm_k_basin.s
  cbm_k_bsout.s
  cbm_k_chkin.s
  cbm_k_chrin.s
	cbm_k_chrout.s
  cbm_k_ciout.s 
  cbm_k_ckout.s
  cbm_k_clall.s
  cbm_k_close.s
  cbm_k_clrch.s
  cbm_k_getin.s
  cbm_k_iobase.s
  cbm_k_listen.s
  cbm_k_load.s
  cbm_k_open.s
  cbm_k_readst.s
  cbm_k_save.s
  cbm_k_scnkey.s
  cbm_k_second.s
  cbm_k_setlfs.s
  cbm_k_setnam.s
  cbm_k_talk.s
  cbm_k_tksa.s
  cbm_k_udtim.s
  cbm_k_unlsn.s
  cbm_k_untlk.s
)

# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily. It can also be called in an interrupt.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)
target_include_directories(commodore-c BEFORE PUBLIC .)
