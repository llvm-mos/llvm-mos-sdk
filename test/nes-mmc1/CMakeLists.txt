cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C ASM)
include(CTest)

function(add_mesen_test executable)
  add_test(NAME test-${executable} COMMAND ${MESEN_COMMAND} --testrunner
           $<TARGET_FILE:${executable}> ${CMAKE_CURRENT_SOURCE_DIR}/mesen.lua)
endfunction()

add_executable(minimal minimal.c)
add_mesen_test(minimal)
