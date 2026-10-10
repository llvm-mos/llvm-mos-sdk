# Targets whose platform sources change often enough that the inner build
# cannot be trusted to notice.
set(TEST_TARGETS_NEEDING_PLATFORM_SYNC mega65)

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
      -DCMAKE_C_FLAGS=${config_flag}
      -DCMAKE_CXX_FLAGS=${config_flag}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
      ${ARGN}
    INSTALL_COMMAND ""
    BUILD_ALWAYS On
    TEST_AFTER_INSTALL On
    EXCLUDE_FROM_ALL YES
    DEPENDS mos-platform)
  # ExternalProject boundaries hide platform source changes from the inner
  # build, so a target whose platform is being worked on has to be cleaned or
  # it runs against stale objects. Opt-in: cleaning every target on every run
  # rebuilds all of them from scratch.
  if(target IN_LIST TEST_TARGETS_NEEDING_PLATFORM_SYNC)
    ExternalProject_Add_Step(test-${target} platform-sync
      COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --target clean
      COMMENT "Cleaning test-${target} to pick up platform changes"
      DEPENDEES configure
      DEPENDERS build
      ALWAYS 1)
  endif()

  add_dependencies(test test-${target})
  set_property(TARGET test-${target} PROPERTY
    ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/test/${target})
endfunction()

add_custom_target(test)
add_test_target(apple2)
add_test_target(nes-nrom)
add_test_target(nes-cnrom)
add_test_target(nes-gtrom)
add_test_target(nes-mmc1)
add_test_target(nes-mmc3)
add_test_target(nes-unrom)
add_test_target(nes-unrom-512)
add_test_target(atari2600-4k)
add_test_target(atari2600-3e)
add_test_target(atari8-dos)
add_test_target(atari8-cart-std)
if(XMEGA65_COMMAND)
  add_test_target(mega65
    -DXMEGA65_COMMAND=${XMEGA65_COMMAND}
    -DPYTHON3_COMMAND=${PYTHON3_COMMAND}
    -DD81_SCRIPT=${CMAKE_SOURCE_DIR}/mos-platform/mega65/d81.py)
endif()
