add_platform_library(mega65-crt fast_math.cc)
target_include_directories(mega65-crt PRIVATE ${CMAKE_SOURCE_DIR}/mos-platform/common/crt)
merge_libraries(mega65-crt common-crt)
