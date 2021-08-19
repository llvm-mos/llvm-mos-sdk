.text
; Function that performs an indirect call through the pointer in RS4. JSRing to
; this routine effectively performs an indirect JSR, since the RTS in the callee
; will return to the original JSR location, ignoring this stub. All arguments
; and return values are trivially forwarded (RS4 is callee-saved and can never
; contain arguments).
.global __call_indir
__call_indir:
  jmp (__rc8)
