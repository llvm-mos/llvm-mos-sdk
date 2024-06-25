platform(commodore PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES cbm.h TYPE INCLUDE)
install(FILES
  cbm.inc
  cbm_kernal.inc
  DESTINATION ${ASMINCDIR})
install(FILES commodore.ld TYPE LIB)

add_platform_library(commodore-crt0)
merge_libraries(commodore-crt0
  common-copy-zp-data
  common-zero-bss
)

add_platform_library(commodore-c
  abort.c
  char-conv.c
  getchar.c
  putchar.c
  cbm_k_acptr.c
  cbm_k_basin.c
  cbm_k_bsout.c
  cbm_k_chkin.s
  cbm_k_chkout.s
  cbm_k_chrin.c
  cbm_k_chrout.c
  cbm_k_cint.c
  cbm_k_ciout.c
  cbm_k_ckout.s
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

  close.s
  diskcmd.s
  filedes.s
  filename.s
  filetype.s
  filevars.s
  open.s
  oserror.s
  read.s
  rwcommon.s
  scratch.s
  sysremove.s
  sysrename.s
  translate-filename.cc
  write.s
)

target_include_directories(commodore-c BEFORE PUBLIC .)
target_link_libraries(commodore-c PRIVATE common-asminc)
