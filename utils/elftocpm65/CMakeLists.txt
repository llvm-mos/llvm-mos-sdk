add_executable(elftocpm65 elftocpm65.cc)
install(TARGETS elftocpm65)

find_package(PkgConfig REQUIRED)

find_package(fmt)
target_link_libraries(elftocpm65 fmt::fmt)
