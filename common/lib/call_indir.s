.text
; Function that performs an indirect call through the pointer
; __call_indir_target. JSRing to this routine effectively performs an indirect
; JSR, since the RTS in the callee will return to the original JSR location,
; ignoring this stub. All arguments and return values are trivially forwarded.
.global __call_indir
__call_indir:
  jmp (__call_indir_target)