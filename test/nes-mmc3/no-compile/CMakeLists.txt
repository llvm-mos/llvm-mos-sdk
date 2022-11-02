set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)

add_no_compile_test(prg-ram-too-big)
add_no_compile_test(prg-rom-too-big)
add_no_compile_test(prg-rom-too-big-fixed)
target_link_options(prg-rom-too-big-fixed PRIVATE -Tcommon.ld -Tc-in-ram.ld -Tprg-rom-fixed.ld)
add_no_compile_test(prg-rom-too-small)
