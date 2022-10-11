/* CP/M entrypoints for C.
 *
 * © 2022 David Given
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE
 * file in the project root for the full text.
 */

#ifndef CPM_H
#define CPM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Standard FCB used for file access. */

typedef struct __attribute__((packed))
{
    uint8_t dr;     /* drive number (1-based, or 0 for default) */
    uint8_t f[11];  /* filename, space padded */
    uint8_t ex;     /* extent low: set to zero on open and otherwise ignore */
    uint8_t s1;     /* spare: ignore */
    uint8_t s2;     /* extent high: ignore */
    uint8_t rc;     /* number of records in this extent: ignore */
    uint8_t al[16]; /* allocation map: ignore */
    uint8_t cr;     /* current record: ignore */
    uint16_t r;     /* random-access pointer: set when doing random-access calls */
    uint8_t r2;     /* random-access overflow: used only by cpm_seek_to_end */
}
FCB;

/* Rename control block, used only by cpm_rename_file. */

typedef struct __attribute__((packed))
{
    uint8_t dr;          /* drive number (1-based, or 0 for default) */
    uint8_t src[11];     /* source filename */
    uint8_t _padding[5]; /* unused; ignore */
    uint8_t dest[11];    /* destination filename */
}
RCB;

/* Directory entry on disk */

typedef struct __attribute__((packed))
{
    uint8_t us;     /* user number */
    uint8_t f[11];  /* filename, space padded */
    uint8_t ex;     /* extent low */
    uint8_t s1;     /* unused */
    uint8_t s2;     /* extent high */
    uint8_t rc;     /* number of records in the last extent in this dirent */
    uint8_t al[16]; /* allocation map */
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
extern uint8_t cpm_cmdlinelen;
extern char cpm_cmdline[0x7f];
extern uint8_t cpm_errno;

/*  0 */ extern __attribute__((leaf)) void _Noreturn cpm_warmboot(void);
/*  1 */ extern __attribute__((leaf)) uint8_t cpm_conin(void);
/*  2 */ extern __attribute__((leaf)) void cpm_conout(uint8_t b);
/*  3 */ extern __attribute__((leaf)) uint8_t cpm_auxin(void);
/*  4 */ extern __attribute__((leaf)) void cpm_auxout(uint8_t b);
/*  5 */ extern __attribute__((leaf)) void cpm_lstout(uint8_t b);
/*  6 */ extern __attribute__((leaf)) uint8_t cpm_conio(uint8_t b);
/*  7 */ extern __attribute__((leaf)) uint8_t cpm_get_iobyte(void);
/*  8 */ extern __attribute__((leaf)) void cpm_set_iobyte(uint8_t iob);
/*  9 */ extern __attribute__((leaf)) void cpm_printstring_i(uint16_t s);
         extern                       void cpm_printstring(const char* s); /* $-terminated */
/* 10 */ extern __attribute__((leaf)) uint8_t cpm_readline(uint8_t* buffer);
/* 11 */ extern __attribute__((leaf)) uint8_t cpm_const(void);
/* 12 */ extern __attribute__((leaf)) uint16_t cpm_get_version(void);
/* 13 */ extern __attribute__((leaf)) void cpm_reset_disk_system(void);
/* 14 */ extern __attribute__((leaf)) void cpm_select_drive(uint8_t disk);
/* 15 */ extern __attribute__((leaf)) uint8_t cpm_open_file_i(uint16_t fcb);
         extern                       uint8_t cpm_open_file(FCB* fcb);
/* 16 */ extern __attribute__((leaf)) uint8_t cpm_close_file_i(uint16_t fcb);
         extern                       uint8_t cpm_close_file(FCB* fcb);
/* 17 */ extern __attribute__((leaf)) uint8_t cpm_findfirst_i(uint16_t fcb);
         extern                       uint8_t cpm_findfirst(FCB* fcb);
/* 18 */ extern __attribute__((leaf)) uint8_t cpm_findnext_i(uint16_t fcb);
         extern                       uint8_t cpm_findnext(FCB* fcb);
/* 19 */ extern __attribute__((leaf)) uint8_t cpm_delete_file_i(uint16_t fcb);
         extern                       uint8_t cpm_delete_file(FCB* fcb);
/* 20 */ extern __attribute__((leaf)) uint8_t cpm_read_sequential_i(uint16_t fcb);
         extern                       uint8_t cpm_read_sequential(FCB* fcb);
/* 21 */ extern __attribute__((leaf)) uint8_t cpm_write_sequential_i(uint16_t fcb);
         extern                       uint8_t cpm_write_sequential(FCB* fcb);
/* 22 */ extern __attribute__((leaf)) uint8_t cpm_make_file_i(uint16_t fcb);
         extern                       uint8_t cpm_make_file(FCB* fcb);
/* 23 */ extern __attribute__((leaf)) uint8_t cpm_rename_file_i(uint16_t rcb);
         extern                       uint8_t cpm_rename_file(RCB* rcb);
/* 24 */ extern __attribute__((leaf)) uint16_t cpm_get_login_vector(void);
/* 25 */ extern __attribute__((leaf)) uint8_t cpm_get_current_drive(void);
/* 26 */ extern __attribute__((leaf)) void cpm_set_dma_i(uint16_t ptr);
         extern                       void cpm_set_dma(void* ptr);
/* 27 */ extern __attribute__((leaf)) uint16_t cpm_get_allocation_vector_i(void);
         extern                       uint8_t* cpm_get_allocation_vector(void);
/* 28 */ extern __attribute__((leaf)) void cpm_write_protect_drive(void);
/* 29 */ extern __attribute__((leaf)) uint16_t cpm_get_readonly_vector(void);
/* 30 */ extern __attribute__((leaf)) uint8_t cpm_set_file_attributes_i(uint16_t fcb);
         extern                       uint8_t cpm_set_file_attributes(FCB* fcb);
/* 31 */ extern __attribute__((leaf)) uint16_t cpm_get_dpb_i(void);
         extern                       DPB* cpm_get_dpb(void);
/* 32 */ extern __attribute__((leaf)) uint8_t cpm_get_set_user(uint8_t user);
/* 33 */ extern __attribute__((leaf)) uint8_t cpm_read_random_i(uint16_t fcb);
         extern                       uint8_t cpm_read_random(FCB* fcb);
/* 34 */ extern __attribute__((leaf)) uint8_t cpm_write_random_i(uint16_t fcb);
         extern                       uint8_t cpm_write_random(FCB* fcb);
/* 35 */ extern __attribute__((leaf)) void cpm_seek_to_end_i(uint16_t fcb);
         extern                       void cpm_seek_to_end(FCB* fcb);
/* 36 */ extern __attribute__((leaf)) void cpm_seek_to_seq_pos_i(uint16_t fcb);
         extern                       void cpm_seek_to_seq_pos(FCB* fcb);
/* 37 */ extern __attribute__((leaf)) uint8_t cpm_reset_drives(uint16_t drive_bitmap);
/* 40 */ extern __attribute__((leaf)) uint8_t cpm_write_random_filled_i(uint16_t fcb);
         extern                       uint8_t cpm_write_random_filled(FCB* fcb);

#define cpm_get_user() cpm_get_set_user(0xff)
#define cpm_set_user(u) cpm_get_set_user(u)

extern __attribute__((leaf)) uint8_t cpm_bios_const(void);
extern __attribute__((leaf)) uint8_t cpm_bios_conin(void);
extern __attribute__((leaf)) void cpm_bios_conout(uint8_t c);
extern                       uint16_t cpm_bios_seldsk_i(uint8_t disk);
extern                       DPH* cpm_bios_seldsk(uint8_t disk);
extern __attribute__((leaf)) void cpm_bios_setsec_i(uint16_t sector); /* actually only 24 bits */
extern                       void cpm_bios_setsec(uint32_t* sector); /* actually only 24 bits */
extern __attribute__((leaf)) void cpm_bios_setdma_i(uint16_t dma);
extern                       void cpm_bios_setdma(void* dma);
extern __attribute__((leaf)) uint8_t cpm_bios_read(void);
extern __attribute__((leaf)) uint8_t cpm_bios_write(uint8_t deblock);
extern __attribute__((leaf)) void cpm_bios_relocate(uint8_t zp, uint8_t mem);
extern __attribute__((leaf)) uint16_t cpm_bios_gettpa(void);
extern __attribute__((leaf)) void cpm_bios_settpa(uint8_t start, uint8_t end);
extern __attribute__((leaf)) uint16_t cpm_bios_getzp(void);
extern __attribute__((leaf)) void cpm_bios_setzp(uint8_t start, uint8_t end);

#ifdef __cplusplus
}
#endif

#endif

// vim: ts=4 sw=4 et

