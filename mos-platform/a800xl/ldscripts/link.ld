/* Atari800XL XEX file linker script.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .xex_header 0x2000 - 12 : {
      /* XEX magic number. */
      SHORT(0xffff),
      /* First byte of Run vector. */
      SHORT(0x02e0),
      /* Last byte of Run vector. */
      SHORT(0x02e1),
      /* Segment to be loaded to Run vector. */
      SHORT(_start),
      /* Address where first byte of main segment should be loaded. */
      SHORT(__load_begin),
      /* Address of last byte of main segment. */
      SHORT(__load_end - 1),
      /* The main segment follows. */
    }

    INCLUDE c_sections.ld
}

/* Provide 128 imaginary (zero page) registers located in 0x80 - 0xff range.
   Atari OS uses first 128 bytes (0x00 - 0x7f) of zero page itself.
   Remaining locations are intended for use by user program, but remember that
   Basic and Floating Point routines also use this part of zero page.
*/

ASSERT(__load_begin == 0x2000, "text at incorrect address.")

PROVIDE(__rc0 = 0x80);
INCLUDE imag_reg/127.ld
ASSERT(__rc0 == 0x0080, "Inconsistent zero page map.")
ASSERT(__rc127 == 0x00ff, "Inconsistent zero page map.")
