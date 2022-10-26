set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)

add_no_compile_test(chr-ram-too-big)
add_no_compile_test(chr-rom-non-pow2)
add_no_compile_test(chr-rom-too-big)
add_no_compile_test(prg-rom-too-big)
add_no_compile_test(prg-ram-too-big)
