cmake_minimum_required(VERSION 3.18)

project(test-mega65 LANGUAGES C)

include(../test.cmake)

# MEGA65 test via xmega65 emulator. The test binary signals pass/fail
# through the xemu control register at $D6CF.
function(add_mega65_test name)
  set(source_dir ".")
  if(ARGC GREATER 1)
    set(source_dir ${ARGV1})
  endif()
  if(NOT XMEGA65_COMMAND)
    return()
  endif()
  add_executable(${name}.prg ${source_dir}/${name}.c)
  add_test(NAME test-${name} COMMAND
    ${XMEGA65_COMMAND} -headless -sleepless -testing
    -prg $<TARGET_FILE:${name}.prg> -prgmode 65)
  set_tests_properties(test-${name} PROPERTIES TIMEOUT 10)
endfunction()

# MEGA65 HDOS test: virtualizes SD card file access via Hyppo hypervisor.
# Creates an hdos directory next to the test binary; the caller populates
# it with test data files (see add_custom_command examples).
function(add_mega65_hdos_test name)
  set(source_dir ".")
  if(ARGC GREATER 1)
    set(source_dir ${ARGV1})
  endif()
  if(NOT XMEGA65_COMMAND)
    return()
  endif()
  add_executable(${name}.prg ${source_dir}/${name}.c)

  add_custom_command(TARGET ${name}.prg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:${name}.prg>/${name}_hdos
    COMMENT "Creating HDOS directory for ${name}")

  add_test(NAME test-${name} COMMAND
    ${XMEGA65_COMMAND} -headless -sleepless -testing -fastboot
    -hdosvirt -hdosdir $<TARGET_FILE_DIR:${name}.prg>/${name}_hdos
    -prg $<TARGET_FILE:${name}.prg> -prgmode 65)
  set_tests_properties(test-${name} PROPERTIES TIMEOUT 10)
endfunction()

# MEGA65 disk test: creates a D81 with test data, injects the PRG via -prg,
# and mounts the D81 on device 8. Signals through $D6CF like the others.
function(add_mega65_disk_test name)
  set(source_dir ".")
  set(extra_files ${ARGN})
  if(ARGC GREATER 1)
    set(source_dir ${ARGV1})
    list(REMOVE_AT extra_files 0)
  endif()
  if(NOT XMEGA65_COMMAND)
    return()
  endif()
  if(NOT PYTHON3_COMMAND)
    return()
  endif()
  add_executable(${name}.prg ${source_dir}/${name}.c)

  # extra arguments are PATH=CBMNAME specs to put on the image
  add_custom_command(TARGET ${name}.prg POST_BUILD
    COMMAND ${PYTHON3_COMMAND} ${D81_SCRIPT}
      $<TARGET_FILE_DIR:${name}.prg>/${name}.d81 -n test -i 01 ${extra_files}
    COMMENT "Creating D81 for ${name}")

  add_test(NAME test-${name} COMMAND
    ${XMEGA65_COMMAND} -headless -sleepless -testing
    -prg $<TARGET_FILE:${name}.prg> -prgmode 65
    -8 $<TARGET_FILE_DIR:${name}.prg>/${name}.d81)
  set_tests_properties(test-${name} PROPERTIES TIMEOUT 10)
endfunction()

# Payload shared by the hyppo and hyppo-fileio fixtures: DE AD BE EF CA FE BA BE
string(ASCII 222 173 190 239 202 254 186 190 _test_payload)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/TEST.BIN" "${_test_payload}")

# d81.py checks its own format code; no emulator needed, only python3.
if(PYTHON3_COMMAND)
  add_test(NAME test-d81 COMMAND ${PYTHON3_COMMAND} ${D81_SCRIPT} --selftest)
  set_tests_properties(test-d81 PROPERTIES TIMEOUT 10)
endif()

add_mega65_test(kernal)
add_mega65_test(kernal-far)

# Load address ($7101 LE) plus 8 bytes; no $00, which string(ASCII) cannot hold.
string(ASCII 1 113 222 173 190 239 202 254 186 190 _disk_test_data)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/TEST.PRG" "${_disk_test_data}")

add_mega65_disk_test(disk "." "${CMAKE_CURRENT_BINARY_DIR}/TEST.PRG=test")

add_mega65_hdos_test(hyppo)
if(TARGET hyppo.prg)
  add_custom_command(TARGET hyppo.prg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_BINARY_DIR}/TEST.BIN"
      "$<TARGET_FILE_DIR:hyppo.prg>/hyppo_hdos/TEST.BIN"
    COMMENT "Copying TEST.BIN to hyppo hdos directory")
endif()

add_mega65_test(hyppo-status)

add_mega65_hdos_test(hyppo-dir)
if(TARGET hyppo-dir.prg)
  # Create two small text files for findfile/readdir tests
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/FILE1.TXT" "hello")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/FILE2.TXT" "world")
  # A subdirectory as well, so chdir has somewhere to go.
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/INNER.TXT" "inner")
  add_custom_command(TARGET hyppo-dir.prg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_BINARY_DIR}/FILE1.TXT"
      "$<TARGET_FILE_DIR:hyppo-dir.prg>/hyppo-dir_hdos/FILE1.TXT"
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_BINARY_DIR}/FILE2.TXT"
      "$<TARGET_FILE_DIR:hyppo-dir.prg>/hyppo-dir_hdos/FILE2.TXT"
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_BINARY_DIR}/INNER.TXT"
      "$<TARGET_FILE_DIR:hyppo-dir.prg>/hyppo-dir_hdos/SUBDIR/INNER.TXT"
    COMMENT "Copying test files to hyppo-dir hdos directory")
endif()

add_mega65_hdos_test(hyppo-fileio)
if(TARGET hyppo-fileio.prg)
  add_custom_command(TARGET hyppo-fileio.prg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_BINARY_DIR}/TEST.BIN"
      "$<TARGET_FILE_DIR:hyppo-fileio.prg>/hyppo-fileio_hdos/TEST.BIN"
    COMMENT "Copying TEST.BIN to hyppo-fileio hdos directory")
endif()
