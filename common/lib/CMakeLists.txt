include(AddObjectFile)

include_directories(../include)

add_object_file(crt0 crt0.s)

add_library(common_crt OBJECT call_indir.s tmp.s)

add_library(common_c OBJECT stub.c)
