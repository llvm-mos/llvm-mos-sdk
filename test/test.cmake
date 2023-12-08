include(CTest)

add_library(test-lib-mesen ${CMAKE_CURRENT_SOURCE_DIR}/../test-lib-mesen.c)
target_include_directories(test-lib-mesen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(test-lib-emutest ${CMAKE_CURRENT_SOURCE_DIR}/../test-lib-emutest.c)
target_include_directories(test-lib-emutest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

function(add_emutest_test name binext source_dir libretro_core)
  add_executable(${name}.${binext} ${source_dir}/${name}.c)
  target_link_libraries(${name}.${binext} test-lib-emutest)
  get_property(libretro_shared_lib VARIABLE PROPERTY ${libretro_core})
  add_test(NAME test-${name} COMMAND ${EMUTEST_COMMAND} -T
    -L ${libretro_shared_lib}
    -r $<TARGET_FILE:${name}.${binext}>
    -t ${CMAKE_CURRENT_SOURCE_DIR}/../emutest.lua)
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
      -DCMAKE_EXPORT_COMPILE_COMMANDS=${CMAKE_EXPORT_COMPILE_COMMANDS}
    )
  set_property(TEST ${target}-no-compile PROPERTY WILL_FAIL YES)
endfunction()

function(add_vcs_test name)
  set(source_dir ".")
  if(ARGC GREATER 1)
    set(source_dir ${ARGV1})
  endif()
  add_emutest_test(${name} a26 ${source_dir} LIBRETRO_STELLA_CORE)
endfunction()

function(add_nes_test name)
  set(source_dir ".")
  if(ARGC GREATER 1)
    set(source_dir ${ARGV1})
  endif()
  add_emutest_test(${name} nes ${source_dir} LIBRETRO_MESEN_CORE)
endfunction()
