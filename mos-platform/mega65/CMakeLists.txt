platform(mega65 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()
install(FILES
    _45E100.h
    _dmagic.h
    _sdcard.h
    _vic3.h
    _vic4.h
    dma.hpp
    mega65.h
TYPE INCLUDE)

install(FILES link.ld TYPE LIB)
install(PROGRAMS d81.py TYPE BIN)

add_platform_library(mega65-crt0)
merge_libraries(mega65-crt0
  common-init-stack
  common-exit-loop
)

add_platform_object_file(mega65-basic-header basic-header.o basic-header.S)
add_platform_object_file(mega65-unmap-basic unmap-basic.o unmap-basic.S)

add_platform_library(mega65-c
  cbm_k_cint.c
  cbm_k_load.c
  cbm_k_save.c
  filevars.s
  kernal.S
  mega65_k_addkey.c
  mega65_k_lda_far.c
  mega65_k_sta_far.c
  mega65_k_cmp_far.c
  mega65_k_close_all.c
  mega65_k_getio.c
  mega65_k_getlfs.c
  mega65_k_load.c
  mega65_k_lkupla.c
  mega65_k_lkupsa.c
  mega65_k_plot.c
  mega65_k_savefl.c
  mega65_k_rdtim.c
  mega65_k_scrorg.c
  mega65_k_setbnk.c
  mega65_k_setmsg.c
  mega65_k_settim.c
  mega65_k_swapper.c
  mega65_k_sysflags.c
  mega65_h_attach.c
  mega65_h_dirio.c
  mega65_h_drive.c
  mega65_h_fileio.c
  mega65_h_d81write_en.c
  mega65_h_findfile.c
  mega65_h_mkfile.c
  mega65_h_loadfile.c
  mega65_h_setname.c
  mega65_h_setname_page.c
  mega65_h_get_proc_desc.c
  mega65_h_locate_freezeslot.c
  mega65_h_unfreeze_from_slot.c
  mega65_h_read_freeze_region_list.c
  mega65_h_get_freeze_slot_count.c
  mega65_h_writefile.c
  mega65_h_getversion.c
  mega65_h_geterrorcode.c
)
target_compile_options(mega65-c PRIVATE -mcpu=mos45gs02)
target_include_directories(mega65-c BEFORE PUBLIC .
  ${CMAKE_CURRENT_SOURCE_DIR}/../c64
  ${CMAKE_CURRENT_SOURCE_DIR}/../commodore)
