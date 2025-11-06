platform(fds COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  bios.inc
  DESTINATION ${ASMINCDIR})
install(FILES
  bios.h
  irq.h
  mapper.h
TYPE INCLUDE)

add_platform_object_file(fds-crt0-o crt0.o)
add_platform_object_file(fds-reset-o reset.o reset.s)

add_platform_library(fds-c
  bios.s

  fds_bios_AdjustFileCount.s
  fds_bios_AppendFile.s
  fds_bios_CheckDiskHeader.c
  fds_bios_CheckFileCount.s
  fds_bios_Delay131.c
  fds_bios_Delayms.s
  fds_bios_DisObj.c
  fds_bios_DisPF.c
  fds_bios_DisPFObj.c
  fds_bios_EnObj.c
  fds_bios_EnPF.c
  fds_bios_EnPFObj.c
  fds_bios_FileMatchTest.c
  fds_bios_GetDiskInfo.s
  fds_bios_GetNumFiles.c
  fds_bios_LoadFiles.s
  fds_bios_MemFill.s
  fds_bios_Nam2PixelConv.c
  fds_bios_OrPads.c
  fds_bios_Pixel2NamConv.c
  fds_bios_ReadDownExpPads.c
  fds_bios_ReadDownPads.c
  fds_bios_ReadDownVerifyPads.c
  fds_bios_ReadKeyboard.s
  fds_bios_ReadOrDownPads.c
  fds_bios_ReadOrDownVerifyPads.c
  fds_bios_ReadPads.c
  fds_bios_SetFileCount.s
  fds_bios_SetFileCount1.s
  fds_bios_SetNumFiles.c
  fds_bios_SkipFiles.c
  fds_bios_SpriteDMA.c
  fds_bios_UploadObject.c
  fds_bios_VINTWait.c
  fds_bios_VRAMFill.s
  fds_bios_WriteFile.s

  irq.c
  irq.s
  mapper.c
)
target_include_directories(fds-c BEFORE PUBLIC .)
target_link_libraries(fds-c PRIVATE common-asminc)
