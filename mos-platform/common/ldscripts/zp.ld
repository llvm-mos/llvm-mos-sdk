.zp.data : {
  __zp_data_start = .;
  *(.zp.data .zp.data.*)
} >zp AT>ram
__zp_data_load_start = LOADADDR(.zp.data);
__zp_data_size = SIZEOF(.zp.data);

.zp.bss (NOLOAD) : {
  __zp_bss_start = .;
  *(.zp.bss .zp.bss.*)
} >zp
__zp_bss_size = SIZEOF(.zp.bss);

.zp (NOLOAD) : {
  *(.zp .zp.*)
} >zp
