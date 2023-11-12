
include(../test.cmake)

target_sources(test-lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../atari2600-common/test-lib-vcs.c)

target_include_directories(test-lib BEFORE PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../atari2600-common/)

add_vcs_test(minimal ../atari2600-common)
add_vcs_test(zeropage-max ../atari2600-common)
