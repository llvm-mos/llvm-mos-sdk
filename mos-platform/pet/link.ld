/* Commodore PET PRG file linker script.                                                                 
 *                                                                                                       
 * Produces a PRG file with a SYS command to start the program.                                          
 */

PROVIDE(__ram_size = 32);
ASSERT(__ram_size <= 32,
       "RAM size must be <= 32 (8x96 and SuperPETs are not supported by this target)")
ASSERT(__ram_size >= 8,
       "RAM size must be at least 8")

__basic_zp_start = 0x0002;
__basic_zp_end = 0x008D;

MEMORY {
    ram (rw) : ORIGIN = 0x0401, LENGTH = (__ram_size * 1024) - 0x0401
}

INCLUDE commodore.ld

/* Grow stack downwards from end of RAM */
__stack = (__ram_size * 1024) - 1;

OUTPUT_FORMAT {
    /* Tells the PET LOAD command where to place the file's contents. */
    SHORT(0x0401)
    TRIM(ram)
}
