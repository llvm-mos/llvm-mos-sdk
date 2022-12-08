/* Atari800 cartridge linker scripts. */

INCLUDE stdcart.ld
INCLUDE cart-rom-fixed.ld

OUTPUT_FORMAT {
  FULL(cart_rom)
}
