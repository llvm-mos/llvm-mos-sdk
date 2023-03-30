/* Commodore PET PRG file linker script.                                                                 
 *                                                                                                       
 * Produces a PRG file with a SYS command to start the program.                                          
 */

MEMORY {
    ram (rw) : ORIGIN = 0x0401, LENGTH = 0x7BFF
}

INCLUDE commodore.ld

/* Grow stack downwards from end of RAM */
__stack = 0x7FFF;

OUTPUT_FORMAT {
    /* Tells the PET LOAD command where to place the file's contents. */
    SHORT(0x0401)
    TRIM(ram)
}
