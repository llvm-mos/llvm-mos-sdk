.include "imag.inc"
.text

;
; void cx16_k_monitor(void) __attribute__((noreturn));
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-monitor
;
.global cx16_k_monitor
cx16_k_monitor:
	jmp	__MONITOR
