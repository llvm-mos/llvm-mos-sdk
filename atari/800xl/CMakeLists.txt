include_directories(include)

configure_file(800xl.cfg ..)

add_subdirectory(include)
add_subdirectory(ldscripts)
add_subdirectory(lib)
