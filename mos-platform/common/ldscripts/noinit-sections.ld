*(.noinit .noinit.* NULL INIT ZPSAVE)
/* This helps ensure all chunk sizes have the low bit free for use as a flag.
 * IMPORTANT: it has to be ALIGN(., 2) rather than just ALIGN(2) because the
 * former generates a relocatable symbol but the latter generates an absolute
 * symbol. This causes platforms which produce relocatable binaries (e.g.
 * CP/M-65) to go horribly wrong. */
__heap_start = ALIGN(., 2);
