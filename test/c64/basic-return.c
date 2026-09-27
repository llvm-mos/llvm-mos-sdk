/* Linked with save-basic.o: main returns and the program hands control back to
 * BASIC, which prints its READY. prompt. Checks that BASIC's ROM is switched
 * back in at exactly that point (see unmap-basic.S). */
int main(void) { return 0; }
