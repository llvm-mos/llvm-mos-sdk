.global __stack

.section .noinit, "wa", @nobits
stack_start:
	.fill 2*1024
__stack:

