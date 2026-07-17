include(platform)

if (CMAKE_CROSSCOMPILING)
  add_compile_options(-flto)
else()
  # Make nested build directory cross-compiling to MOS, but using this
  # CMakeLists.txt.
  ExternalProject_Add(mos-platform
    SOURCE_DIR   ${CMAKE_SOURCE_DIR}
    BINARY_DIR   build
    INSTALL_DIR  build/install
    STAMP_DIR    build/stamp
    TMP_DIR      build/tmp
    DOWNLOAD_DIR build
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/llvm-mos-toolchain.cmake
      -DCMAKE_C_COMPILER=${LLVM_MOS_C_COMPILER}
      -DCMAKE_CXX_COMPILER=${LLVM_MOS_CXX_COMPILER}
      -DCMAKE_ASM_COMPILER=${LLVM_MOS_ASM_COMPILER}
      -DCMAKE_C_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_CXX_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_ASM_FLAGS=${LLVM_MOS_ARCH_FLAGS}
      -DCMAKE_EXPORT_COMPILE_COMMANDS=${CMAKE_EXPORT_COMPILE_COMMANDS}
    USES_TERMINAL_CONFIGURE On
    USES_TERMINAL_BUILD On
    USES_TERMINAL_INSTALL On
    BUILD_ALWAYS On)
  ExternalProject_Get_Property(mos-platform INSTALL_DIR)
  install(DIRECTORY ${INSTALL_DIR}/ DESTINATION .)

  # Clean the build directories with the host project.
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
    ADDITIONAL_CLEAN_FILES build ../examples)

  find_package(Doxygen OPTIONAL_COMPONENTS dot)
  if (Doxygen_FOUND)
    set(DOXYGEN_FILE_PATTERNS *)
    set(DOXYGEN_EXTENSION_MAPPING no_extension=C++)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXCLUDE_SYMBOLS __*)
    set(DOXYGEN_EXCLUDE_PATTERNS *.c *.cc *.s *.S *.cfg *.ld *.awk __*)
    doxygen_add_docs(doxygen .)
  endif()
endif()

add_subdirectory(common)
add_subdirectory(atari2600-common)
add_subdirectory(atari2600-4k)
add_subdirectory(atari2600-3e)
add_subdirectory(atari5200-supercart)
add_subdirectory(atari8-common)
add_subdirectory(atari8-dos)
add_subdirectory(atari8-cart-std)
add_subdirectory(atari8-cart-xegs)
add_subdirectory(atari8-cart-megacart)
add_subdirectory(commodore)
add_subdirectory(c64)
add_subdirectory(c128)
add_subdirectory(cpm65)
add_subdirectory(cx16)
add_subdirectory(eater)
add_subdirectory(geos-cbm)
add_subdirectory(mega65)
add_subdirectory(neo6502)
add_subdirectory(sim)
add_subdirectory(nes)
add_subdirectory(nes-action53)
add_subdirectory(nes-cnrom)
add_subdirectory(nes-gtrom)
add_subdirectory(nes-nrom)
add_subdirectory(nes-mmc1)
add_subdirectory(nes-mmc3)
add_subdirectory(nes-unrom)
add_subdirectory(nes-unrom-512)
add_subdirectory(fds)
add_subdirectory(osi-c1p)
add_subdirectory(dodo)
add_subdirectory(pet)
add_subdirectory(rpc8e)
add_subdirectory(lynx)
add_subdirectory(lynx-bll)
add_subdirectory(lynx-lnx)
add_subdirectory(pce-common)
add_subdirectory(pce)
add_subdirectory(pce-cd)
add_subdirectory(rp6502)
add_subdirectory(supervision)
add_subdirectory(vic20)
