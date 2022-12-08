add_library(common-asminc INTERFACE)
target_include_directories(common-asminc BEFORE INTERFACE .)
install(FILES imag.inc DESTINATION ${ASMINCDIR})
