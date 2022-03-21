.global __do_copy_data

.section .init.20,"axR",@progbits
__do_copy_data:
  jsr __copy_data
