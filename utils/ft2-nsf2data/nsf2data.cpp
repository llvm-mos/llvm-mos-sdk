// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_NESASM 0
#define OUT_CA65 1
#define OUT_ASM6 2
#define OUT_LLVM 3

char DB[8];
char DW[8];
char LL[8];

unsigned char memory[65536];
bool log;
bool change;
int wait_;
int duration;

int volume[4];

bool volume_all_zero;

int regs[32];

FILE *out_file;
int out_size;

unsigned char *nsf_data;
int nsf_size;

int nsf_songs;
int nsf_load_adr;
int nsf_init_adr;
int nsf_play_adr;

unsigned char effect_data[256];

int effect_ptr;
int effect_last_zero_volume_ptr;

bool effect_stop;
int effect_error;

bool pal;
bool ntsc;

void effect_add(unsigned char n) {
  if (effect_ptr < 256)
    effect_data[effect_ptr] = n;

  ++effect_ptr;
}

void effect_flush_wait(void) {
  while (wait_ >= 126) {
    effect_add(126 + 1);
    wait_ -= 126;
  }

  if (wait_ >= 0)
    effect_add(wait_ + 1);

  wait_ = 0;
}

static inline unsigned char mem_rd(int adr) {
  if (adr < 0x2000)
    return memory[adr & 0x7ff]; // RAM

  return memory[adr]; // ROM
}

static inline void mem_wr(int adr, unsigned char data) {
  const unsigned char regmap[32] = {0x80, 0, 0x81, 0x82, 0x83, 0, 0x84, 0x85,
                                    0x86, 0, 0x87, 0x88, 0x89, 0, 0x8a};

  if (adr < 0x2000) // RAM
  {
    memory[adr & 0x7ff] = data;
    return;
  }

  if (adr >= 0x5c00 && adr < 0x8000) // extra RAM
  {
    memory[adr] = data;
    return;
  }

  if (adr < 0x4018) // APU registers
  {
    if (!log)
      return;

    if (adr == 0x4001 || adr == 0x4005) {
      if (data & 0x80) {
        printf("\nError: sweep effects are not supported.\n");

        effect_error = 1;
      }

      return;
    }

    if (adr == 0x4000 || adr == 0x4002 || adr == 0x4003 || adr == 0x4004 ||
        adr == 0x4006 || adr == 0x4007 || adr == 0x4008 || adr == 0x400a ||
        adr == 0x400b || adr == 0x400c ||
        adr == 0x400e) // check if the register is allowed
    {
      if (regs[adr - 0x4000] != data) {
        if (!change)
          effect_flush_wait();

        switch (adr) {
        case 0x4000:
          volume[0] = data & 0x0f;
          break;
        case 0x4004:
          volume[1] = data & 0x0f;
          break;
        case 0x4008:
          volume[2] = data & 0x7f;
          break;
        case 0x400c:
          volume[3] = data & 0x0f;
          break;
        }

        if (!volume_all_zero) {
          if (!volume[0] && !volume[1] && !volume[2] && !volume[3]) {
            volume_all_zero = true;
            effect_last_zero_volume_ptr = effect_ptr;
          }
        } else {
          if (volume[0] || volume[1] || volume[2] || volume[3]) {
            volume_all_zero = false;
          }
        }

        effect_add(regmap[adr - 0x4000]);
        effect_add(data);

        regs[adr - 0x4000] = data;

        change = true;
      }
    }

    if (adr == 0x4015 && !data) // catch the C00 effect
    {
      change = true;
      effect_stop = true;
    }
  }
}

#include "cpu2a03.h"

void convert_effects(void) {
  int i, cnt, col, song, mode;

  effect_error = 0;

  for (song = 0; song < nsf_songs; ++song) {
    printf("Effect %i", song);

    for (mode = 0; mode < 2; ++mode) {
      if (!mode && !ntsc)
        continue;
      if (mode && !pal)
        continue;

      fprintf(out_file, "%ssfx_%s_%i:\n", LL, !mode ? "ntsc" : "pal", song);

      memset(memory, 0, 65536);
      memcpy(memory + nsf_load_adr, nsf_data + 0x80, nsf_size - 0x80);

      for (i = 0; i < 32; i++)
        regs[i] = -1;

      regs[0x00] = 0x30;
      regs[0x04] = 0x30;
      regs[0x08] = 0x00;
      regs[0x0c] = 0x30;

      volume[0] = 0;
      volume[1] = 0;
      volume[2] = 0;
      volume[3] = 0;

      volume_all_zero = true;

      cpu_reset();

      CPU.A = song;
      CPU.X = mode;
      CPU.PC.hl = nsf_init_adr;
      CPU.S = 0xFC;          // reserve 3 bytes on stack
      memory[0x01FF] = 0x00; // BRK instruction to cause jam
      memory[0x01FE] = 0x01; // return address 0x01FF-1
      memory[0x01FD] = 0xFE;

      log = false;

      for (i = 0; i < 2000; ++i)
        cpu_tick(); // 2000 is enough for FT init

      cpu_reset();

      effect_ptr = 0;
      effect_last_zero_volume_ptr = 0;

      log = true;
      cnt = 0;
      wait_ = -1;
      duration = 0;
      effect_stop = false;

      while (!effect_stop) {
        CPU.PC.hl = nsf_play_adr;
        CPU.jam = false;
        CPU.S = 0xff;
        change = false;

        for (i = 0; i < 30000 / 4 && !effect_error && !effect_stop; ++i) {
          cpu_tick();

          if (CPU.jam)
            break;
        }

        if (!change)
          ++wait_;

        ++duration;

        if (duration > 10 * 60) {
          printf("\nError: effect is too long, Cxx at end of the effect may be "
                 "missing.");
          effect_error = 1;
          return;
        }
      }

      if (!volume_all_zero) // if a channel is still active, record its duration
      {
        if (wait_ > 0)
          effect_flush_wait();
      } else // if there is no active channels, trim effect to the point just
             // before last volume has been set to zero
      {
        effect_ptr = effect_last_zero_volume_ptr;
      }

      effect_add(0); // end

      printf("\t%s\t%i", !mode ? "NTSC" : "PAL", effect_ptr);

      if (effect_ptr > 256) {
        printf("\nError: effect data is too long, should be 256 bytes max.\n");
        effect_error = 1;
      }

      if (effect_error)
        return;

      col = 0;

      for (i = 0; i < effect_ptr; ++i) {
        if (!col)
          fprintf(out_file, "\t%s ", DB);

        fprintf(out_file, "$%2.2x", effect_data[i]);

        ++col;

        if (col == 16 || i == effect_ptr - 1) {
          fprintf(out_file, "\n");
          col = 0;
        } else {
          fprintf(out_file, ",");
        }
      }

      out_size += effect_ptr;
    }

    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  char name[1024];
  int i, outtype;
  FILE *file;

  if (argc < 2) {
    printf("nsf2data converter for FamiTone2 audio library\n");
    printf("by Shiru (shiru@mail.ru) 04'17\n");
    printf(
        "Usage: nsf2data.exe filename.nsf [-nesasm,-ca65,-asm6][-pal or -ntsc]\n");

    return 1;
  }

  outtype = OUT_LLVM;
  pal = true;
  ntsc = true;

  for (i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "-nesasm"))
      outtype = OUT_NESASM;
    if (!strcmp(argv[i], "-ca65"))
      outtype = OUT_CA65;
    if (!strcmp(argv[i], "-asm6"))
      outtype = OUT_ASM6;
    if (!strcmp(argv[i], "-pal")) {
      pal = true;
      ntsc = false;
    }
    if (!strcmp(argv[i], "-ntsc")) {
      pal = false;
      ntsc = true;
    }
  }

  printf("Output format: ");

  switch (outtype) {
  case OUT_NESASM:
    printf("NESASM\n");
    strcpy(DB, ".db");
    strcpy(DW, ".dw");
    strcpy(LL, ".");
    break;

  case OUT_CA65:
    printf("CA65\n");
    strcpy(DB, ".byte");
    strcpy(DW, ".word");
    strcpy(LL, "@");
    break;

  case OUT_ASM6:
    printf("Asm6\n");
    strcpy(DB, ".db");
    strcpy(DW, ".dw");
    strcpy(LL, "@");
    break;

  case OUT_LLVM:
    printf("LLVM\n");
    strcpy(DB, ".byte");
    strcpy(DW, ".word");
    strcpy(LL, ".L");
    break;
  }

  printf("Output mode: ");

  if (pal && ntsc)
    printf("PAL and NTSC\n");
  else if (pal)
    printf("PAL only\n");
  else
    printf("NTSC only\n");

  printf("\n");

  file = fopen(argv[1], "rb");

  if (!file) {
    printf("Can't open file\n");

    return 1;
  }

  fseek(file, 0, SEEK_END);
  nsf_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  nsf_data = (unsigned char *)malloc(nsf_size);
  fread(nsf_data, nsf_size, 1, file);
  fclose(file);

  nsf_songs = nsf_data[0x06];

  nsf_load_adr = nsf_data[0x08] + (nsf_data[0x09] << 8);
  nsf_init_adr = nsf_data[0x0a] + (nsf_data[0x0b] << 8);
  nsf_play_adr = nsf_data[0x0c] + (nsf_data[0x0d] << 8);

  if (nsf_songs > 128) {
    printf("Too many sound effects in the file, up to 128 is supported\n");
    free(nsf_data);

    return 1;
  }

  for (i = 0x70; i < 0x78; ++i) {
    if (nsf_data[i]) {
      printf("Bankswitching is not supported\n");
      free(nsf_data);

      return 1;
    }
  }

  if (nsf_data[0x7b]) {
    printf("Expansion chips are not supported\n");
    free(nsf_data);

    return 1;
  }

  printf("%i effects found\n\n", nsf_songs);

  strcpy(name, argv[1]);

  for (i = strlen(name) - 1; i >= 0; --i) {
    if (name[i] == '.') {
      name[i] = 0;
      break;
    }
  }

  if (outtype != OUT_CA65 && outtype != OUT_LLVM)
    strcat(name, ".asm");
  else
    strcat(name, ".s");

  out_file = fopen(name, "wt");

  out_size = 4;

  if (ntsc)
    out_size += nsf_songs * 2;
  if (pal)
    out_size += nsf_songs * 2;

  fprintf(out_file,
          ";this file for FamiTone2 libary generated by nsf2data tool\n\n");

  fprintf(out_file, "sounds:\n");

  if (ntsc && pal) {
    fprintf(out_file, "\t%s %sntsc\n", DW, LL);
    fprintf(out_file, "\t%s %spal\n", DW, LL);
  } else {
    if (ntsc) {
      fprintf(out_file, "\t%s %sntsc\n", DW, LL);
      fprintf(out_file, "\t%s %sntsc\n", DW, LL);
    } else {
      fprintf(out_file, "\t%s %spal\n", DW, LL);
      fprintf(out_file, "\t%s %spal\n", DW, LL);
    }
  }

  if (ntsc) {
    fprintf(out_file, "%sntsc:\n", LL);

    for (i = 0; i < nsf_songs; ++i)
      fprintf(out_file, "\t%s %ssfx_ntsc_%i\n", DW, LL, i);
  }

  if (pal) {
    fprintf(out_file, "%spal:\n", LL);

    for (i = 0; i < nsf_songs; ++i)
      fprintf(out_file, "\t%s %ssfx_pal_%i\n", DW, LL, i);
  }

  fprintf(out_file, "\n");

  convert_effects();

  fclose(out_file);
  free(nsf_data);

  if (effect_error)
    return effect_error;

  printf("\nTotal data size %i bytes\n", out_size);

  return 0;
}
