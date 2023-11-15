
include(../test.cmake)

target_sources(test-lib-emutest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../atari2600-common/test-lib-vcs.c)

target_include_directories(test-lib-emutest BEFORE PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../atari2600-common/)

add_vcs_test(minimal ../atari2600-common)
add_vcs_test(zeropage-max ../atari2600-common)

add_vcs_test(frame-simple ../atari2600-common)
set_property(TEST test-frame-simple PROPERTY ENVIRONMENT EMUTEST_FB_CRC_PASS=3714305448)
