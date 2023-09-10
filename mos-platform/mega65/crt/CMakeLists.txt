add_platform_library(mega65-crt mul_m65.cc divmod_m65.cc divmod_m65.h)
target_include_directories(mega65-crt PRIVATE ${CMAKE_SOURCE_DIR}/mos-platform/common/crt)
merge_libraries(mega65-crt common-crt)
