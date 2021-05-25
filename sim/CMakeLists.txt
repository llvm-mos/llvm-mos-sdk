include_directories(include)

configure_file(sim.cfg ..)

add_subdirectory(include)
add_subdirectory(ldscripts)
add_subdirectory(lib)
add_subdirectory(sim)
