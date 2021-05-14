include_directories(include)

configure_file(64.cfg ..)

add_subdirectory(include)
add_subdirectory(ldscripts)
add_subdirectory(lib)
