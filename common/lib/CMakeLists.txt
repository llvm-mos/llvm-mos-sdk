include(AddObjectFile)

add_object_file(crt0 crt0.s)
add_library(common_os OBJECT tmp.s)
