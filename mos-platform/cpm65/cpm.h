#ifndef CPM_H
#define CPM_H

#include <stdint.h>

typedef struct __attribute__((packed))
{
    uint8_t dr;
    uint8_t f[11];
    uint8_t ex;
    uint8_t s1;
    uint8_t s2;
    uint8_t rc;
    uint8_t al[16];
    uint8_t cr;
    uint16_t r;
    uint8_t r2;
}
FCB;

typedef struct __attribute__((packed))
{
    uint8_t dr;
    uint8_t src[11];
    uint8_t _padding[5];
    uint8_t dest[11];
}
RCB;

typedef struct __attribute__((packed))
{
    uint8_t us;
    uint8_t f[11];
    uint8_t ex;
    uint8_t s1;
    uint8_t s2;
    uint8_t rc;
    uint8_t al[16];
}
DIRE;

typedef struct __attribute__((packed))
{
    uint16_t spt;    /* number of 128-byte sectors per track (unused on CP/M-65) */
    uint8_t bsh;     /* block shift; 3=1kB, 4=2kB, 5=4kB etc */
    uint8_t blm;     /* block mask; 0x07=1kB, 0x0f=2kB, 0x1f=4k etc */
    uint8_t exm;     /* extent mask */
    uint16_t dsm;    /* maximum block number */
    uint16_t drm;    /* maximum directory entry number */
    uint8_t al[2];   /* directory allocation bitmap */
    uint16_t cks;    /* checksum vector size */
    uint16_t off;    /* number of reserved tracks */
}
DPB;

typedef struct __attribute__((packed))
{
    uint8_t* xlt;       /* address of translation vector */
    uint8_t scratch[6]; /* BDOS scratchpad */
    uint8_t* dirbuf;    /* address of directory scratchpad */
    DPB* dpb;       /* address of DPB */
    uint8_t* csv;       /* address of disk change scratchpad */
    uint8_t* alv;       /* address of allocation bitmap */
}
DPH;

enum
{
    CPME_OK        = 0x00, /* success (usually) */
    CPME_NOBLOCK   = 0x01, /* or EOF */
    CPME_DISKFULL  = 0x02, /* no free blocks on disk */
    CPME_CANTCLOSE = 0x03, /* can't write extent back to disk */
    CPME_NOEXTENT  = 0x04, /* only on random access reads */
    CPME_DIRFULL   = 0x05, /* no free dirents on disk */
    CPME_BADFCB    = 0x09, /* FCB couldn't be parsed */
    CPME_FAILED    = 0xff, /* general purpose failure code */
};

extern FCB cpm_fcb; /* primary FCB */
extern FCB cpm_fcb2; /* secondary FCB (special purpose, overlaps cpm_fcb) */

extern uint8_t cpm_default_dma[128]; /* also contains the parsed command line */
extern uint8_t cpm_ram[];
extern uint8_t* cpm_ramtop;
extern uint8_t cpm_cmdlinelen;
extern char cpm_cmdline[0x7f];
extern uint8_t cpm_errno;

/*  0 */ extern void _Noreturn cpm_warmboot(void);
/*  1 */ extern uint8_t cpm_conin(void);
/*  2 */ extern void cpm_conout(uint8_t b);
/*  3 */ extern uint8_t cpm_auxin(void);
/*  4 */ extern void cpm_auxout(uint8_t b);
/*  5 */ extern void cpm_lstout(uint8_t b);
/*  6 */ extern uint8_t cpm_conio(uint8_t b);
/*  7 */ extern uint8_t cpm_get_iobyte(void);
/*  8 */ extern void cpm_set_iobyte(uint8_t iob);
/*  9 */ extern void cpm_printstring_i(uint16_t s);
         static void cpm_printstring(const char* s) /* $-terminated */
            { cpm_printstring_i((uint16_t) s); }
/* 10 */ extern uint8_t cpm_readline(uint8_t* buffer);
/* 11 */ extern uint8_t cpm_const(void);
/* 12 */ extern uint16_t cpm_get_version(void);
/* 13 */ extern void cpm_reset_disk_system(void);
/* 14 */ extern void cpm_select_drive(uint8_t disk);
/* 15 */ extern uint8_t cpm_open_file_i(uint16_t fcb);
         static uint8_t cpm_open_file(FCB* fcb)
            { return cpm_open_file_i((uint16_t) fcb); }
/* 16 */ extern uint8_t cpm_close_file_i(uint16_t fcb);
         static uint8_t cpm_close_file(FCB* fcb)
            { return cpm_close_file_i((uint16_t) fcb); }
/* 17 */ extern uint8_t cpm_findfirst_i(uint16_t fcb);
         static uint8_t cpm_findfirst(FCB* fcb)
            { return cpm_findfirst_i((uint16_t) fcb); }
/* 18 */ extern uint8_t cpm_findnext_i(uint16_t fcb);
         static uint8_t cpm_findnext(FCB* fcb)
            { return cpm_findnext_i((uint16_t) fcb); }
/* 19 */ extern uint8_t cpm_delete_file_i(uint16_t fcb);
         static uint8_t cpm_delete_file(FCB* fcb)
            { return cpm_delete_file_i((uint16_t) fcb); }
/* 20 */ extern uint8_t cpm_read_sequential_i(uint16_t fcb);
         static uint8_t cpm_read_sequential(FCB* fcb)
            { return cpm_read_sequential_i((uint16_t) fcb); }
/* 21 */ extern uint8_t cpm_write_sequential_i(uint16_t fcb);
         static uint8_t cpm_write_sequential(FCB* fcb)
            { return cpm_write_sequential_i((uint16_t) fcb); }
/* 22 */ extern uint8_t cpm_make_file_i(uint16_t fcb);
         static uint8_t cpm_make_file(FCB* fcb)
            { return cpm_make_file_i((uint16_t) fcb); }
/* 23 */ extern uint8_t cpm_rename_file_i(uint16_t rcb);
         static uint8_t cpm_rename_file(RCB* rcb)
            { return cpm_rename_file_i((uint16_t) rcb); }
/* 24 */ extern uint16_t cpm_get_login_vector(void);
/* 25 */ extern uint8_t cpm_get_current_drive(void);
/* 26 */ extern void cpm_set_dma_i(uint16_t ptr);
         static void cpm_set_dma(void* ptr)
            { cpm_set_dma_i((uint16_t) ptr); }
/* 27 */ extern uint16_t cpm_get_allocation_vector_i(void);
         static uint8_t* cpm_get_allocation_vector(void)
            { return (uint8_t*) cpm_get_allocation_vector_i(); }
/* 28 */ extern void cpm_write_protect_drive(void);
/* 29 */ extern uint16_t cpm_get_readonly_vector(void);
/* 30 */ extern uint8_t cpm_set_file_attributes_i(uint16_t fcb);
         static uint8_t cpm_set_file_attributes(FCB* fcb)
            { return cpm_set_file_attributes_i((uint16_t) fcb); }
/* 31 */ extern uint16_t cpm_get_dpb_i(void);
         static DPB* cpm_get_dpb(void)
            { return (DPB*) cpm_get_dpb_i(); }
/* 32 */ extern uint8_t cpm_get_set_user(uint8_t user);
/* 33 */ extern uint8_t cpm_read_random_i(uint16_t fcb);
/* 33 */ static uint8_t cpm_read_random(FCB* fcb)
            { return cpm_read_random_i((uint16_t) fcb); }
/* 34 */ extern uint8_t cpm_write_random_i(uint16_t fcb);
/* 34 */ static uint8_t cpm_write_random(FCB* fcb)
            { return cpm_write_random_i((uint16_t) fcb); }
/* 35 */ extern void cpm_seek_to_end_i(uint16_t fcb);
/* 35 */ static void cpm_seek_to_end(FCB* fcb)
            { return cpm_seek_to_end_i((uint16_t) fcb); }
/* 36 */ extern void cpm_seek_to_seq_pos_i(uint16_t fcb);
/* 36 */ static void cpm_seek_to_seq_pos(FCB* fcb)
            { return cpm_seek_to_seq_pos_i((uint16_t) fcb); }
/* 37 */ extern uint8_t cpm_reset_drives(uint16_t drive_bitmap);
/* 40 */ extern uint8_t cpm_write_random_filled_i(uint16_t fcb);
         static uint8_t cpm_write_random_filled(FCB* fcb)
            { return cpm_write_random_filled_i((uint16_t) fcb); }

#define cpm_get_user() cpm_get_set_user(0xff)
#define cpm_set_user(u) cpm_get_set_user(u)

extern int cpm_bios_const(void);
extern int cpm_bios_conin(void);
extern void cpm_bios_conout(uint8_t c);
extern DPH* cpm_bios_seldsk(uint8_t disk);
extern void cpm_bios_setsec(uint32_t* sector); /* actually only 24 bits */
extern void cpm_bios_setdma(void* dma);
extern int cpm_bios_read(void);
extern int cpm_bios_write(uint8_t deblock);
extern int cpm_bios_listst(void);

#endif

// vim: ts=4 sw=4 et

