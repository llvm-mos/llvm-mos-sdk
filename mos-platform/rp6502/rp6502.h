#ifndef _RP6502_H
#define _RP6502_H

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
  unsigned int errno;
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

/* OS operation numbers */

#define RIA_OP_EXIT 0xFF
#define RIA_OP_ZXSTACK 0x00
#define RIA_OP_XREG 0x01
#define RIA_OP_PHI2 0x02
#define RIA_OP_CODEPAGE 0x03
#define RIA_OP_LRAND 0x04
#define RIA_OP_STDIN_OPT 0x05
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
#define RIA_OP_LSEEK 0x1A
#define RIA_OP_UNLINK 0x1B
#define RIA_OP_RENAME 0x1C

/* C API for the operating system. */

int xregn(char device, char channel, unsigned char address, unsigned char count,
          ...);
int phi2(void);
int codepage(void);
long lrand(void);
int stdin_opt(unsigned long ctrl_bits, unsigned char str_length);
int read_xstack(void *buf, unsigned count, int fildes);
int read_xram(unsigned buf, unsigned count, int fildes);
int write_xstack(const void *buf, unsigned count, int fildes);
int write_xram(unsigned buf, unsigned count, int fildes);

/* Temporary home for standard library headers. */

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR 0x03
#define O_CREAT 0x10
#define O_TRUNC 0x20
#define O_APPEND 0x40
#define O_EXCL 0x80

#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2

int open(const char *name, int flags, ...);
int read(int fildes, void *buf, unsigned count);
int write(int fildes, const void *buf, unsigned count);
int close(int fd);
long lseek(int fd, long offset, int whence);
unsigned char _sysremove(const char *name);
unsigned char _sysrename(const char *oldpath, const char *newpath);

/* XREG location helpers */

#define xreg_ria_keyboard(...) xreg(0, 0, 0, __VA_ARGS__)
#define xreg_ria_mouse(...) xreg(0, 0, 1, __VA_ARGS__)
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

/* Values in __oserror are the union of these FatFs errors and errno.h */

typedef enum {
  FR_OK = 32,      /* Succeeded */
  FR_DISK_ERR,     /* A hard error occurred in the low level disk I/O layer */
  FR_INT_ERR,      /* Assertion failed */
  FR_NOT_READY,    /* The physical drive cannot work */
  FR_NO_FILE,      /* Could not find the file */
  FR_NO_PATH,      /* Could not find the path */
  FR_INVALID_NAME, /* The path name format is invalid */
  FR_DENIED, /* Access denied due to prohibited access or directory full */
  FR_EXIST,  /* Access denied due to prohibited access */
  FR_INVALID_OBJECT,  /* The file/directory object is invalid */
  FR_WRITE_PROTECTED, /* The physical drive is write protected */
  FR_INVALID_DRIVE,   /* The logical drive number is invalid */
  FR_NOT_ENABLED,     /* The volume has no work area */
  FR_NO_FILESYSTEM,   /* There is no valid FAT volume */
  FR_MKFS_ABORTED,    /* The f_mkfs() aborted due to any problem */
  FR_TIMEOUT, /* Could not get a grant to access the volume within defined
                 period */
  FR_LOCKED,  /* The operation is rejected according to the file sharing policy
               */
  FR_NOT_ENOUGH_CORE,     /* LFN working buffer could not be allocated */
  FR_TOO_MANY_OPEN_FILES, /* Number of open files > FF_FS_LOCK */
  FR_INVALID_PARAMETER    /* Given parameter is invalid */
} FRESULT;

#endif /* _RP6502_H */
