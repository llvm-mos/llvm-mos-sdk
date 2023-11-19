#include <string.h>
#include <mapper.h>
#include <peekpoke.h>

#include "test-lib-vcs.h"

// XRAM on the VCS has different areas for read vs. write

typedef struct {
  char buf[256];
} XRAMStruct;

#define OTHER_BANK 1

// XRAM on the VCS has different areas for read vs. write
// declare xram_data_read and xram_data_write as XRAM variables
DECLARE_XRAM_VARIABLE(0, XRAMStruct xram_a);
DECLARE_XRAM_VARIABLE(0, XRAMStruct xram_b);
DECLARE_XRAM_VARIABLE(OTHER_BANK, XRAMStruct xram_c);

// TODO: test banked_call_ram()

void test_ram(void) {
  char x;

  ram_select(0);

  POKE(MAPPER_XRAM_WRITE | 0x7f0, 0xaa);
  x = PEEK(MAPPER_XRAM_READ | 0x3f0);
  if (x != 0xaa) test_failed();

  xram_write(0x3f1, 0x55);
  x = xram_read(0x3f1);
  if (x != 0x55) test_failed();

  xram_write(0x3f2, 0xaa);
  x = xram_read(0x3f2);
  if (x != 0xaa) test_failed();

  xram_a_write.buf[0] = 1;
  x = xram_a_read.buf[0];
  if (x != 1) test_failed();
  xram_b_write.buf[0] = 3;
  x = xram_b_read.buf[0];
  if (x != 3) test_failed();
  x = xram_a_read.buf[0];
  if (x != 1) test_failed();

  ram_select(OTHER_BANK);

  xram_a_write.buf[0] = 2;
  x = xram_a_read.buf[0];
  if (x != 2) test_failed();

  ram_select(0);

  x = xram_a_read.buf[0];
  if (x != 1) test_failed();
  x = xram_b_read.buf[0];
  if (x != 3) test_failed();
  x = xram_c_read.buf[0];
  if (x != 1) test_failed();
}

int main(void) {
  test_ram();
  test_passed();
  return 0;
}
