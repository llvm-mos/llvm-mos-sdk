set(CMAKE_C_FLAGS "-O2 -Wall -Wextra")
add_executable(sim netlist_sim.c perfect6502.c sim.c)