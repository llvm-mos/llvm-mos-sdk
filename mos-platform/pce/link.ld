
ASSERT((__early_start_end - __early_start_start) == 35, "early_start code size changed - edit link.ld to match crt0/crt0.S")
ASSERT(__early_start_end == 0xfff6, "early_start code size changed - edit link.ld to match crt0/crt0.S")
