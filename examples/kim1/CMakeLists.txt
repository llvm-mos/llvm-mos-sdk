add_executable(kim1-hello hello.c)
install_example(kim1-hello)

if(PLATFORM STREQUAL kim1-60k)
  add_executable(kim1-hello-60k hello-60k.c)
  install_example(kim1-hello-60k)
endif()
