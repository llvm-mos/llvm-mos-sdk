cmake_minimum_required(VERSION 3.18)

project(test-nes-mmc1 LANGUAGES C)
include(CTest)

function(add_mesen_test executable)
  add_test(NAME test-${executable} COMMAND ${MESEN_COMMAND} --testrunner
           $<TARGET_FILE:${executable}> ${CMAKE_CURRENT_SOURCE_DIR}/mesen.lua)
endfunction()

add_executable(minimal minimal.c)
add_mesen_test(minimal)

function(add_no_compile_test target)
  add_test(NAME {target}-no-compile COMMAND ${CMAKE_CTEST_COMMAND}
    --build-and-test ${CMAKE_CURRENT_SOURCE_DIR}/no-compile
                    ${CMAKE_CURRENT_BINARY_DIR}/no-compile
    --build-generator ${CMAKE_GENERATOR}
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-target ${target}
    --build-options
      -DLLVM_MOS=${LLVM_MOS}
      -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    )
endfunction()

add_no_compile_test(minimal)
