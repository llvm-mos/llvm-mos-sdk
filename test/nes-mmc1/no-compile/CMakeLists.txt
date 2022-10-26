cmake_minimum_required(VERSION 3.18)

set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)

add_no_compile_test(chr-rom-too-big)
add_no_compile_test(chr-rom-non-pow2)
add_no_compile_test(chr-ram-too-big)
add_no_compile_test(chr-ram-uneven-banks)
add_no_compile_test(chr-nvram-uneven-banks)
add_no_compile_test(prg-ram-too-big)
add_no_compile_test(prg-ram-uneven-banks)
add_no_compile_test(prg-nvram-uneven-banks)
