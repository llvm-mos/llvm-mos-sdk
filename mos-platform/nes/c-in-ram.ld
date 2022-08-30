/* Place C sections in NES RAM. */
REGION_ALIAS("c_ram_vma", ram)
REGION_ALIAS("c_ram_lma", ram)
__stack = 0x07ff;
