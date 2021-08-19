.text
; Function that performs an indirect call through the pointer
; __call_indir_target. JSRing to this routine effectively performs an indirect
; JSR, since the RTS in the callee will return to the original JSR location,
; ignoring this stub. All arguments and return values are trivially forwarded.
; TODO: Remove this version in favor of __call_indir2
.global __call_indir
__call_indir:
  jmp (__call_indir_target)

; Function that performs an indirect call through the pointer in RS4. JSRing to
; this routine effectively performs an indirect JSR, since the RTS in the callee
; will return to the original JSR location, ignoring this stub. All arguments
; and return values are trivially forwarded (RS4 is callee-saved and can never
; contain arguments).
; TODO: Rename this to __call_indir
.global __call_indir2
__call_indir2:
  jmp (__rc8)
