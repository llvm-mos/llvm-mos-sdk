.data : {
    __data_start = .;
    *(.data .data.*)
    __data_end = .;
}
__data_load_start = LOADADDR(.data);
__data_size = SIZEOF(.data);
