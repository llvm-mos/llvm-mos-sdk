add_executable(demo_vcslib.a26 demo_vcslib.c)
target_compile_options(demo_vcslib.a26 PRIVATE "-Os")
install_example(demo_vcslib.a26)
