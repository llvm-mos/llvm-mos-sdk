#ifndef _RP6502_H
#define _RP6502_H

#ifdef __cplusplus
extern "C" {
#endif

/* RP6502 RIA $FFE0-$FFF9 */
struct __RP6502 {
  const unsigned char ready;
  unsigned char tx;
  const unsigned char rx;
  const unsigned char vsync;
  unsigned char rw0;
  unsigned char step0;
  unsigned int addr0;
  unsigned char rw1;
  unsigned char step1;
  unsigned int addr1;
  unsigned char xstack;
  unsigned int errno_;
  unsigned char op;
  unsigned char irq;
  const unsigned char spin;
  const unsigned char busy;
  const unsigned char lda;
  unsigned char a;
  const unsigned char ldx;
  unsigned char x;
  const unsigned char rts;
  unsigned int sreg;
};
#define RIA (*(volatile struct __RP6502 *)0xFFE0)

#define RIA_READY_TX_BIT 0x80
#define RIA_READY_RX_BIT 0x40
#define RIA_BUSY_BIT 0x80

/* XSTACK helpers */

void ria_push_long(unsigned long val);
void ria_push_int(unsigned int val);
#define ria_push_char(v) RIA.xstack = v

long ria_pop_long(void);
int ria_pop_int(void);
#define ria_pop_char() RIA.xstack

/* Set the RIA fastcall register */

void ria_set_axsreg(unsigned long axsreg);
void ria_set_ax(unsigned int ax);
#define ria_set_a(v) RIA.a = v

/* Run an OS operation */

int ria_call_int(unsigned char op);
long ria_call_long(unsigned char op);

/* OS operation numbers */

#define RIA_OP_EXIT 0xFF
#define RIA_OP_ZXSTACK 0x00
#define RIA_OP_XREG 0x01
#define RIA_OP_PHI2 0x02
#define RIA_OP_CODE_PAGE 0x03
#define RIA_OP_LRAND 0x04
#define RIA_OP_STDIN_OPT 0x05
#define RIA_OP_ERRNO_OPT 0x06
#define RIA_OP_CLOCK 0x0F
#define RIA_OP_CLOCK_GETRES 0x10
#define RIA_OP_CLOCK_GETTIME 0x11
#define RIA_OP_CLOCK_SETTIME 0x12
#define RIA_OP_CLOCK_GETTIMEZONE 0x13
#define RIA_OP_OPEN 0x14
#define RIA_OP_CLOSE 0x15
#define RIA_OP_READ_XSTACK 0x16
#define RIA_OP_READ_XRAM 0x17
#define RIA_OP_WRITE_XSTACK 0x18
#define RIA_OP_WRITE_XRAM 0x19
#define RIA_OP_LSEEK_CC65 0x1A
#define RIA_OP_UNLINK 0x1B
#define RIA_OP_RENAME 0x1C
#define RIA_OP_LSEEK 0x1D
#define RIA_OP_LSEEK_LLVM 0x1D
#define RIA_OP_SYNCFS 0x1E
#define RIA_OP_STAT 0x1F
#define RIA_OP_OPENDIR 0x20
#define RIA_OP_READDIR 0x21
#define RIA_OP_CLOSEDIR 0x22
#define RIA_OP_TELLDIR 0x23
#define RIA_OP_SEEKDIR 0x24
#define RIA_OP_REWINDDIR 0x25
#define RIA_OP_CHMOD 0x26
#define RIA_OP_UTIME 0x27
#define RIA_OP_MKDIR 0x28
#define RIA_OP_CHDIR 0x29
#define RIA_OP_CHDRIVE 0x2A
#define RIA_OP_GETCWD 0x2B
#define RIA_OP_SETLABEL 0x2C
#define RIA_OP_GETLABEL 0x2D
#define RIA_OP_GETFREE 0x2E

/* C API for the operating system. */

typedef struct {
  unsigned long fsize;
  unsigned fdate;
  unsigned ftime;
  unsigned crdate;
  unsigned crtime;
  unsigned char fattrib;
  char altname[12 + 1];
  char fname[255 + 1];
} f_stat_t;

int xregn(char device, char channel, unsigned char address, unsigned count,
          ...);
int phi2(void);
int code_page(int);
long lrand(void);
int stdin_opt(unsigned long ctrl_bits, unsigned char str_length);
int read_xstack(void *buf, unsigned count, int fildes);
int read_xram(unsigned buf, unsigned count, int fildes);
int write_xstack(const void *buf, unsigned count, int fildes);
int write_xram(unsigned buf, unsigned count, int fildes);
long f_lseek(long offset, int whence, int fildes);
int f_stat(const char *path, f_stat_t *dirent);
int f_opendir(const char *name);
int f_readdir(f_stat_t *dirent, int dirdes);
int f_closedir(int dirdes);
long f_telldir(int dirdes);
int f_seekdir(long offs, int dirdes);
int f_rewinddir(int dirdes);
int f_chmod(const char *path, unsigned char attr, unsigned char mask);
int f_utime(const char *path, unsigned fdate, unsigned ftime, unsigned crdate,
            unsigned crtime);
int f_mkdir(const char *name);
int f_chdrive(const char *name);
int f_getcwd(char *name, int size);
int f_setlabel(const char *name);
int f_getlabel(const char *path, char *label);
int f_getfree(const char *name, unsigned long *free, unsigned long *total);

/* XREG helper macros */

#define xreg__(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3,  \
               _2, _1, count, ...)                                             \
  count
#define xreg_(...)                                                             \
  xreg__(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define xreg(d, c, a, ...) xregn(d, c, a, xreg_(__VA_ARGS__), __VA_ARGS__)

#define xreg_ria_keyboard(...) xreg(0, 0, 0, __VA_ARGS__)
#define xreg_ria_mouse(...) xreg(0, 0, 1, __VA_ARGS__)
#define xreg_ria_gamepad(...) xreg(0, 0, 2, __VA_ARGS__)
#define xreg_vga_canvas(...) xreg(1, 0, 0, __VA_ARGS__)
#define xreg_vga_mode(...) xreg(1, 0, 1, __VA_ARGS__)

/* XRAM structure helpers */

#define xram0_struct_set(addr, type, member, val)                              \
  RIA.addr0 = (unsigned)(&((type *)0)->member) + (unsigned)addr;               \
  switch (sizeof(((type *)0)->member)) {                                       \
  case 1:                                                                      \
    RIA.rw0 = val;                                                             \
    break;                                                                     \
  case 2:                                                                      \
    RIA.step0 = 1;                                                             \
    RIA.rw0 = val & 0xff;                                                      \
    RIA.rw0 = (val >> 8) & 0xff;                                               \
    break;                                                                     \
  case 4:                                                                      \
    RIA.step0 = 1;                                                             \
    RIA.rw0 = (unsigned long)val & 0xff;                                       \
    RIA.rw0 = ((unsigned long)val >> 8) & 0xff;                                \
    RIA.rw0 = ((unsigned long)val >> 16) & 0xff;                               \
    RIA.rw0 = ((unsigned long)val >> 24) & 0xff;                               \
    break;                                                                     \
  }

#define xram1_struct_set(addr, type, member, val)                              \
  RIA.addr1 = (unsigned)(&((type *)0)->member) + (unsigned)addr;               \
  switch (sizeof(((type *)0)->member)) {                                       \
  case 1:                                                                      \
    RIA.rw1 = val;                                                             \
    break;                                                                     \
  case 2:                                                                      \
    RIA.step1 = 1;                                                             \
    RIA.rw1 = val & 0xff;                                                      \
    RIA.rw1 = (val >> 8) & 0xff;                                               \
    break;                                                                     \
  case 4:                                                                      \
    RIA.step1 = 1;                                                             \
    RIA.rw1 = (unsigned long)val & 0xff;                                       \
    RIA.rw1 = ((unsigned long)val >> 8) & 0xff;                                \
    RIA.rw1 = ((unsigned long)val >> 16) & 0xff;                               \
    RIA.rw1 = ((unsigned long)val >> 24) & 0xff;                               \
    break;                                                                     \
  }

typedef struct {
  unsigned char x_wrap; // bool
  unsigned char y_wrap; // bool
  int x_pos_px;
  int y_pos_px;
  int width_chars;
  int height_chars;
  unsigned xram_data_ptr;
  unsigned xram_palette_ptr;
  unsigned xram_font_ptr;
} vga_mode1_config_t;

typedef struct {
  unsigned char x_wrap; // bool
  unsigned char y_wrap; // bool
  int x_pos_px;
  int y_pos_px;
  int width_tiles;
  int height_tiles;
  unsigned xram_data_ptr;
  unsigned xram_palette_ptr;
  unsigned xram_tile_ptr;
} vga_mode2_config_t;

typedef struct {
  unsigned char x_wrap; // bool
  unsigned char y_wrap; // bool
  int x_pos_px;
  int y_pos_px;
  int width_px;
  int height_px;
  unsigned xram_data_ptr;
  unsigned xram_palette_ptr;
} vga_mode3_config_t;

typedef struct {
  int x_pos_px;
  int y_pos_px;
  unsigned xram_sprite_ptr;
  unsigned char log_size;
  unsigned char has_opacity_metadata; // bool
} vga_mode4_sprite_t;

typedef struct {
  int transform[6];
  int x_pos_px;
  int y_pos_px;
  unsigned xram_sprite_ptr;
  unsigned char log_size;
  unsigned char has_opacity_metadata; // bool
} vga_mode4_asprite_t;

#ifdef __cplusplus
}
#endif

#endif /* _RP6502_H */
