#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

#define TRACE 0

// MHz of the simulated CPU accurate timing mode.
const float kMHz = 10;

static const char usage[] =
    "Usage: sim [OPTIONS] [image]\n"
    "\n"
    "6502 simulator.\n"
    "\n"
    "Takes a memory image file.\n"
    "The image file is a collection of blocks. Each block consists of a\n"
    "16-bit starting address, then a 16-bit block size, then that many bytes\n"
    "of contents. Both the address and size are stored little-endian.\n"
    "\n"
    "The simulated 6502 will execute a reset sequence through the vector at\n"
    "$FFFC like a real 6502.\n"
    "\n"
    "Writing to $FFF7 aborts.\n"
    "Writing to $FFF8 quits normally.\n"
    "Writing to $FFF9 writes to stdout.\n"
    "\n"
    "OPTIONS:\n"
    "\t--cycles: Print cycle count to stderr.\n"
    "\t--trace: Print each instruction address to stderr.\n"
    "\t--cmos: Enable 65C02 emulation.\n";

void reset6502(uint8_t cmos);
void step6502();
extern uint32_t clockticks6502;
extern uint16_t pc;
extern uint8_t a, x, y, sp, status;

uint8_t memory[65536];
uint32_t clock_start = 0;
bool shouldPrintCycles = false;
bool shouldTrace = false;
bool cmos = false;
bool input_eof = false;

int8_t read6502(uint16_t address) {
  if (address == 0xfff0) {
    *((uint32_t *)(memory + address)) = clockticks6502 - clock_start;
  } else if (address == 0xfff5) {
    const int c = getchar();
    input_eof = (c == EOF);
    return (int8_t)c;
  } else if (address == 0xfff6) {
    return (int8_t)input_eof;
  }
  return memory[address];
}

void printCycles(void) {
  fprintf(stderr, "%d cycles\n", clockticks6502);
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
    if (shouldPrintCycles)
      printCycles();
    abort();
  case 0xFFF8:
    if (shouldPrintCycles)
      printCycles();
    exit(value);
  case 0xFFF9:
    putchar(value);
    break;
  }
}

bool parseFlag(int *argc, const char ***argv) {
  if (*argc < 2)
    return false;
  const char *flag = (*argv)[1];
  if (!strcmp(flag, "--cycles")) {
    shouldPrintCycles = true;
  } else if (!strcmp(flag, "--trace")) {
    shouldTrace = true;
  } else if (!strcmp(flag, "--cmos")) {
    cmos = true;
  } else
    return false;

  for (int i = 2; i < *argc; ++i) {
    (*argv)[i - 1] = (*argv)[i];
  }
  --*argc;
  return true;
}


int main(int argc, const char *argv[]) {
  while (parseFlag(&argc, &argv));

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

  while (1) {
    // Assumes host is little-endian.
    uint16_t address;
    if (fread(&address, 2, 1, file) != 1) {
      if (feof(file))
        break;
      else {
        fprintf(stderr, "Error reading image file '%s': ", filename);
        perror(NULL);
        return 1;
      }
    }

    uint16_t size;
    if (fread(&size, 2, 1, file) != 1) {
      fprintf(stderr, "Error reading image file '%s': ", filename);
      if (feof(file))
        fputs("expected block size, found EOF.", stderr);
      else
        perror(NULL);
      return 1;
    }

    uint32_t lastAddress = address + size - 1;
    if (lastAddress >= 65536) {
      fprintf(stderr,
              "Invalid block: block of %d bytes at address %d would reach "
              "location %d, which is out of bounds.\n",
              size, address, lastAddress);
      return 1;
    }

    size_t readSize = fread(&memory[address], 1, size, file);
    if (readSize != size) {
      fprintf(stderr, "Error reading image file '%s': ", filename);
      if (feof(file)) {
        fprintf(stderr, "expected %d byte block, found %zu bytes.", size,
                readSize);
      } else
        perror(NULL);
      return 1;
    }
  }

  reset6502(cmos);
  for (;;) {
    if (shouldTrace)
      fprintf(stderr, "%04x a:%02x x:%02x y:%02x s: %02x st:%02x\n", pc, a, x, y, sp, status);
    step6502();
  }
  return 0;
}
