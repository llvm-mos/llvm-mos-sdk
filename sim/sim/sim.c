#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#define TRACE 0

static const char usage[] =
    "Usage: sim [image]\n"
    "\n"
    "6502 simulator.\n"
    "Takes a 64KiB memory image file as its only argument.\n"
    "\n"
    "The simulated 6502 will execute a reset sequence through the vector at\n"
    "$FFFC like a real 6502.\n"
    "Writing to $FFF7 aborts.\n"
    "Writing to $FFF8 quits normally.\n"
    "Writing to $FFF9 writes to stdout.\n";

void reset6502();
void step6502();
extern uint32_t clockticks6502;

uint8_t memory[65536];
uint32_t clock_start = 0;

int8_t read6502(uint16_t address) {
  if(address == 0xfff0) {
    *((uint32_t *)(memory + address)) = clockticks6502 - clock_start;
  }
  return memory[address];
}

void write6502(uint16_t address, uint8_t value) {
  switch (address) {
  default:
    memory[address] = value;
    break;
  case 0xFFF0:
    clock_start = clockticks6502;
    break;
  case 0xFFF7:
    abort();
  case 0xFFF8:
    exit(value);
  case 0xFFF9:
    putchar(value);
    break;
  }
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
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

  reset6502();
  for (;;)
    step6502();
  return 0;
}
