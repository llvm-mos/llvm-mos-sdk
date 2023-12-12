
include(../test.cmake)

#TODO; zp test
#TODO; .bss test
#TODO; .data test

add_a8_test(hw ../atari8-dos)
set_property(TEST test-hw PROPERTY ENVIRONMENT EMUTEST_FB_CRC_PASS=000000000)
