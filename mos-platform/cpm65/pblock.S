.global cpm_fcb
.global cpm_fcb2
.global cpm_default_dma
.global cpm_cmdlinelen
.global cpm_cmdline

.section .pblock, "wa", @nobits
cpm_fcb:	     .fill 37
cpm_fcb2 = cpm_fcb + 33
cpm_default_dma:
cpm_cmdlinelen:  .fill 1
cpm_cmdline:	 .fill 127
