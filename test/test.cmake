include(CTest)

add_library(test-lib ${CMAKE_CURRENT_SOURCE_DIR}/../test-lib.c)

function(add_mesen_test name)
  add_executable(${name} ${name}.c)
  target_link_libraries(${name} test-lib)
  add_test(NAME test-${name} COMMAND ${MESEN_COMMAND} --testrunner
           $<TARGET_FILE:${name}> ${CMAKE_CURRENT_SOURCE_DIR}/../mesen.lua)
endfunction()

function(add_no_compile_test target)
  add_executable(${target} ${target}.c)
  add_test(NAME ${target}-no-compile COMMAND ${CMAKE_CTEST_COMMAND}
    --build-and-test ${CMAKE_CURRENT_SOURCE_DIR}/..
                     ${CMAKE_CURRENT_BINARY_DIR}/${target}
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
