
; the default INIT (which can be overriden) is a stub to enable
; operation of SIC! cartridges, overriding it should be done with
; caution.

.text
.weak _cart_init
_cart_init = 0xbffa - 14
