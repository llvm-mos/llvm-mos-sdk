#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "netlist_sim.h"
#include "perfect6502.h"

static const char usage[] =
    "Usage: sim [image]\n"
    "\n"
    "6502 simulator.\n"
    "Takes a 64KiB memory image file as its only argument.\n"
    "\n"
    "The simulated 6502 will execute a reset sequence through the vector at\n"
    "$FFFC like a real 6502.\n"
    "Writing a nonzero value to $FFF8 quits.\n"
    "Writing to $FFF9 writes to stdout.\n";

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    fputs(usage, stderr);
    return 1;
  }

  const char *filename = argv[1];
  FILE *file = fopen(filename, "rb");
  if (!file) {
    fprintf(stderr, "Could not open '%s': ", filename);
    perror(NULL);
    return 1;
  }

  size_t size = fread(memory, 1, 65536, file);
  if (size != 65536) {
    if (feof(file)) {
      fprintf(stderr,
              "Provided image file '%s' was not exactly 64KiB: was %zu bytes\n",
              filename, size);
    }
  }

  state_t *state = initAndResetChip();
  while (!memory[0xFFF8]) {
    step(state);
    BOOL clk = isNodeHigh(state, 1171);
    if (clk && !readRW(state)) {
      if (readAddressBus(state) == 0xFFF9)
        putchar(readDataBus(state));
    }
  }
  destroyChip(state);

  return 0;
}