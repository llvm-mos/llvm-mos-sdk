function(add_test_target target)
  get_filename_component(llvm_mos ${LLVM_MOS_C_COMPILER} DIRECTORY)
  ExternalProject_Get_Property(mos-platform INSTALL_DIR)
  set(config_flag "--config ${INSTALL_DIR}/bin/mos-${target}.cfg")

  ExternalProject_Add(test-${target}
    SOURCE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/${target}
    INSTALL_DIR  ${CMAKE_BINARY_DIR}/test/${target}
    BINARY_DIR   ${CMAKE_BINARY_DIR}/test/${target}/build
    STAMP_DIR    ${CMAKE_BINARY_DIR}/test/${target}/build/stamp
    TMP_DIR      ${CMAKE_BINARY_DIR}/test/${target}/build/tmp
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/test/${target}/build
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
      -DLLVM_MOS=${llvm_mos}
      -DMESEN_COMMAND=${MESEN_COMMAND}
      -DEMUTEST_COMMAND=${EMUTEST_COMMAND}
      -DLIBRETRO_STELLA_CORE=${LIBRETRO_STELLA_CORE}
      -DLIBRETRO_MESEN_CORE=${LIBRETRO_MESEN_CORE}
      -DLIBRETRO_FCEUMM_CORE=${LIBRETRO_FCEUMM_CORE}
      -DCMAKE_C_FLAGS=${config_flag}
      -DCMAKE_CXX_FLAGS=${config_flag}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
    INSTALL_COMMAND ""
    BUILD_ALWAYS On
    TEST_AFTER_INSTALL On
    EXCLUDE_FROM_ALL YES
    DEPENDS mos-platform)
  add_dependencies(test test-${target})
  set_property(TARGET test-${target} PROPERTY
    ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/test/${target})
endfunction()

add_custom_target(test)
add_test_target(nes-nrom)
add_test_target(nes-cnrom)
add_test_target(nes-gtrom)
add_test_target(nes-mmc1)
add_test_target(nes-mmc3)
add_test_target(nes-unrom)
add_test_target(nes-unrom-512)
add_test_target(atari2600-4k)
add_test_target(atari2600-3e)
