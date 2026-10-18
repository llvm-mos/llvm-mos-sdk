#ifndef _RP6502_H
#define _RP6502_H

#ifdef __cplusplus
extern "C" {
#endif

/* RP6502 VIA $FFD0-$FFDF */
struct __6522 {
  unsigned char prb;    /* Port register B */
  unsigned char pra;    /* Port register A */
  unsigned char ddrb;   /* Data direction register B */
  unsigned char ddra;   /* Data direction register A */
  unsigned char t1_lo;  /* Timer 1, low byte */
  unsigned char t1_hi;  /* Timer 1, high byte */
  unsigned char t1l_lo; /* Timer 1 latch, low byte */
  unsigned char t1l_hi; /* Timer 1 latch, high byte */
  unsigned char t2_lo;  /* Timer 2, low byte */
  unsigned char t2_hi;  /* Timer 2, high byte */
  unsigned char sr;     /* Shift register */
  unsigned char acr;    /* Auxiliary control register */
  unsigned char pcr;    /* Peripheral control register */
  unsigned char ifr;    /* Interrupt flag register */
  unsigned char ier;    /* Interrupt enable register */
  unsigned char pra2;   /* Port register A w/o handshake */
};
#define VIA (*(volatile struct __6522 *)0xFFD0)

/* RP6502 RIA $FFE0-$FFF9 */
struct __RP6502 {
  const unsigned char ready;
  unsigned char tx;
  const unsigned char rx;
  const unsigned char vsync;
  unsigned char rw0;
  signed char step0;
  unsigned int addr0;
  unsigned char rw1;
  signed char step1;
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

__attribute__((leaf)) int ria_spin(void);
static inline unsigned char ria_vsync(void) { return RIA.vsync; }
static inline unsigned char ria_irq_read(void) { return RIA.irq; }
static inline void ria_irq_write(unsigned char mask) { RIA.irq = mask; }

/* OS operation numbers */

#define RIA_OP_EXIT 0xFF
#define RIA_OP_DROP_XSTACK 0x00
#define RIA_OP_XREG 0x01
#define RIA_OP_ARGV 0x08
#define RIA_OP_EXEC 0x09
#define RIA_OP_ATTR_GET 0x0A
#define RIA_OP_ATTR_SET 0x0B
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
#define RIA_OP_RLN_LASTKEY 0x30
#define RIA_OP_RLN_PEEK 0x31
#define RIA_OP_RLN_POKE 0x32
#define RIA_OP_GMTIME 0x3A
#define RIA_OP_LOCALTIME 0x3B
#define RIA_OP_MKTIME 0x3C
#define RIA_OP_STRFTIME 0x3D
#define RIA_OP_TIME_SET 0x3E
#define RIA_OP_TIME_GET 0x3F

static inline void ria_drop(void) { RIA.op = RIA_OP_DROP_XSTACK; }

/* RIA attribute IDs */

#define RIA_ATTR_ERRNO_OPT 0x00
#define RIA_ATTR_PHI2_KHZ 0x01
#define RIA_ATTR_CODE_PAGE 0x02
#define RIA_ATTR_RLN_LENGTH 0x03
#define RIA_ATTR_LRAND 0x04
#define RIA_ATTR_BEL 0x05
#define RIA_ATTR_LAUNCHER 0x06
#define RIA_ATTR_EXIT_CODE 0x07
#define RIA_ATTR_SIGINT 0x08
#define RIA_ATTR_RLN_CAPS 0x09
#define RIA_ATTR_RLN_WIDTH 0x0A
#define RIA_ATTR_RLN_HEIGHT 0x0B
#define RIA_ATTR_RLN_SUPPRESS_NL 0x0C
#define RIA_ATTR_CLK_RUN_MS 0x10
#define RIA_ATTR_CLK_RUN_CS 0x11
#define RIA_ATTR_CLK_RUN_DS 0x12
#define RIA_ATTR_CLK_RUN_S 0x13

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

int ria_execv(const char *path, char *const argv[]);
int ria_execl(const char *path, ...);
long ria_attr_get(unsigned char id);
int ria_attr_set(long val, unsigned char id);
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
int ria_rln_lastkey(char *key, unsigned char *action);
int ria_rln_peek(char *peek, unsigned char *pos);
int ria_rln_poke(const char *poke);
int time_set(long long time);

/* Extended memory */

#define xreg(d, c, a, ...)                                                     \
  xregn(d, c, a, sizeof((long[]){__VA_ARGS__}) / sizeof(long), __VA_ARGS__)
int xregn(char device, char channel, unsigned char address, unsigned count,
          ...);
void xram0_read(void *dest, unsigned src, unsigned count);
void xram1_read(void *dest, unsigned src, unsigned count);
void xram0_write(unsigned dest, const void *src, unsigned count);
void xram1_write(unsigned dest, const void *src, unsigned count);
void xram0_set(unsigned dest, unsigned char val, unsigned count);
void xram1_set(unsigned dest, unsigned char val, unsigned count);
void xram_move(unsigned dest, unsigned src, unsigned count);

static inline unsigned char xram0_peek8(unsigned addr) {
  RIA.addr0 = addr;
  return RIA.rw0;
}

static inline unsigned char xram1_peek8(unsigned addr) {
  RIA.addr1 = addr;
  return RIA.rw1;
}

static inline unsigned xram0_peek16(unsigned addr) {
  RIA.addr0 = addr;
  RIA.step0 = 1;
  unsigned char lo = RIA.rw0;
  return lo | (unsigned)RIA.rw0 << 8;
}

static inline unsigned xram1_peek16(unsigned addr) {
  RIA.addr1 = addr;
  RIA.step1 = 1;
  unsigned char lo = RIA.rw1;
  return lo | (unsigned)RIA.rw1 << 8;
}

static inline void xram0_poke8(unsigned addr, unsigned char val) {
  RIA.addr0 = addr;
  RIA.rw0 = val;
}

static inline void xram1_poke8(unsigned addr, unsigned char val) {
  RIA.addr1 = addr;
  RIA.rw1 = val;
}

static inline void xram0_poke16(unsigned addr, unsigned val) {
  RIA.addr0 = addr;
  RIA.step0 = 1;
  RIA.rw0 = val;
  RIA.rw0 = val >> 8;
}

static inline void xram1_poke16(unsigned addr, unsigned val) {
  RIA.addr1 = addr;
  RIA.step1 = 1;
  RIA.rw1 = val;
  RIA.rw1 = val >> 8;
}

#ifdef __cplusplus
}
#endif

#endif /* _RP6502_H */
