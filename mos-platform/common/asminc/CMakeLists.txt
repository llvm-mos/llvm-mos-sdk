add_library(common-asminc INTERFACE)
target_include_directories(common-asminc BEFORE INTERFACE .)
install(FILES
  errno.inc
  fcntl.inc
  imag.inc
  DESTINATION ${ASMINCDIR})
