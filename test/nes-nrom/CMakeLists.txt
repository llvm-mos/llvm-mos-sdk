cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)
include(CTest)

add_library(test-lib test-lib.c)

function(add_mesen_test name)
  add_executable(${name} ${name}.c)
  target_link_libraries(${name} test-lib)
  add_test(NAME test-${name} COMMAND ${MESEN_COMMAND} --testrunner
           $<TARGET_FILE:${name}> ${CMAKE_CURRENT_SOURCE_DIR}/mesen.lua)
endfunction()

add_mesen_test(minimal)

add_mesen_test(chr-ram)
add_mesen_test(chr-rom)

add_mesen_test(prg-rom-16)
add_mesen_test(prg-rom-32)

add_mesen_test(prg-ram)
add_mesen_test(prg-ram-c)
target_link_options(prg-ram-c PRIVATE -Tcommon.ld -Tc-in-prg-ram.ld)

function(add_no_compile_test target)
  add_test(NAME ${target}-no-compile COMMAND ${CMAKE_CTEST_COMMAND}
    --build-and-test ${CMAKE_CURRENT_SOURCE_DIR}/no-compile
                    ${CMAKE_CURRENT_BINARY_DIR}/no-compile/${target}
    --build-generator ${CMAKE_GENERATOR}
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-target ${target}
    --build-options
      -DLLVM_MOS=${LLVM_MOS}
      -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    )
  set_property(TEST ${target}-no-compile PROPERTY WILL_FAIL YES)
endfunction()

add_no_compile_test(chr-rom-too-big)
add_no_compile_test(chr-rom-non-pow2)
add_no_compile_test(chr-ram-too-big)

add_no_compile_test(prg-rom-too-big)
add_no_compile_test(prg-ram-too-big)
