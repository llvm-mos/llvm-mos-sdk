; PET BASIC header that jumps to _start                            

.section .basic_header,"aR",@progbits
        .short next_line        ; address of next BASIC line                                 
        .short 7773             ; line number: l33t for LLVM, a hint that this program was   
                                                ; compiled with LLVM                         
        .byte 0x9e                      ; SYS keyword BASIC token                            
        .mos_addr_asciz _start, 4       ; the location of the _start symbol, in 4 decimal    
                                                ; ASCII digits                               
next_line:
        .short 0                        ; end of basic program                               


