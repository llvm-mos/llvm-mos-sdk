; KIM-1 monitor ROM entry points
;
; These symbols alias the fixed ROM addresses so C code can call them
; via the standard extern declaration pattern.

OUTCHR = 0x1EA0   ; Transmit character in A to serial terminal
INTCHR = 0x1E5A   ; Receive character from serial terminal into A

.global __kim1_outchr
__kim1_outchr = OUTCHR

.global __kim1_intchr
__kim1_intchr = INTCHR
