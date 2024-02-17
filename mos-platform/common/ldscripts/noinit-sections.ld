*(.noinit .noinit.* NULL INIT ZPSAVE)
/* This helps ensure all chunk sizes have the low bit free for use as a flag. */
__heap_start = ALIGN(., 2);
