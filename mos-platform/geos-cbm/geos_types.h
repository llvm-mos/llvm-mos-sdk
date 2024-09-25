/***********************************************************************
 * geos_types.h
 *
 * This file contains type definitions for use in GEOS applications
 * with llvm-mos C compiler.
 *
 ***********************************************************************/

#ifndef GEOS_TYPES_H
#define GEOS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "geos_constants.h"

/***********************************************************************
 * Generic Definintions
 ***********************************************************************/

typedef uint8_t track_t;  /** a track on a commodore disk drive */
typedef uint8_t sector_t; /** a sector on a commodore disk drive */

typedef void (*vector)(void);

typedef char disk_name_t[DK_NM_ID_LEN]; /** type of a disk  name */
typedef char file_name_t[DK_NM_ID_LEN]; /** type of a file  name */
typedef char prt_drv_name_t[17];        /** type of a printer driver  name */

/** a pair of tr+sc forming a block address */

typedef struct tr_se_pair {
  track_t track;
  sector_t sector;
} tr_se_pair_t;

/** a disk block of track-sector pairs */

typedef struct tr_se_pair file_tr_se_tab_t[128];

_Static_assert(sizeof(file_tr_se_tab_t) == 256,
               "Illegal size of file_tr_se_tab_t");

typedef struct date {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
} date_t;

/***********************************************************************
 * Commodore/GEOS disk block
 ***********************************************************************/

typedef struct disk_block {
  tr_se_pair_t block_chain;
  uint8_t data[254];
} disk_block_t;

_Static_assert(sizeof(disk_block_t) == 256, "Illegal size of disk_block_t");

/***********************************************************************
 * Commodore/GEOS directory entry
 ***********************************************************************/

typedef struct dir_entry {
  dos_file_type_t dos_file_type;
  tr_se_pair_t data_block;
  char name[16];
  tr_se_pair_t header_block;
  file_structure_t structure;
  geos_file_type_t type;
  date_t date;
  uint16_t size_in_blocks;
} dir_entry_t;

_Static_assert(sizeof(dir_entry_t) == 30, "Illegal size: dir_entry_t");

typedef struct cvt_dir_entry {
  dir_entry_t d;
  char signature[28];
} cvt_dir_entry_t;

/***********************************************************************
 * BAM Format / Directory Header
 ***********************************************************************/

/** struct of a bam track in directory header */

typedef struct bam_track {
  uint8_t no_of_se; /** number of sectors in track */
  uint8_t bam[3];   /** BAM sectors 0-20 */
} bam_track_t;

_Static_assert(sizeof(bam_track_t) == 4, "Illegal size of bam_track_t");

/** BAM Format / Directory Header */

typedef struct dir_header {
  tr_se_pair_t dir_block;          /** Always 18,1 */
  char c1541_disk_format;          /** should be 'A' */
  char buffer;                     /** ignored */
  bam_track_t bam_track[35];       /** BAM for tracks 1-35 */
  disk_name_t disk_name;           /** disk name padded with 0xa0 */
  uint16_t disk_id;                /** disk ID */
  char buffer2;                    /** shifted spaces (0xa0) */
  char dos_version;                /** '2' */
  char disk_format;                /** 'A' */
  char buffer3[4];                 /** shifted spaces (0xa0) */
  tr_se_pair_t off_page_dir_block; /** Tr/Sr of off page Directory Block */
  char geos_id[16];                /** GEOS ID string. "GEOS format V1.2" */
  char master_disk; /** =, 'P': P indicates protected master disk */
  char buffer4[66]; /** 0, unused */
} dir_header_t;

_Static_assert(sizeof(dir_header_t) == 256, "Illegal size of dir_header_t");

/***********************************************************************
 * GEOS file header definition
 ***********************************************************************/

typedef struct file_header {
  uint8_t icon_width;     /** Width of icon in bytes, always 3 */
  uint8_t icon_height;    /** Height of icon in pixels, always 21 */
  uint8_t icon_data_type; /** Always 0x80 + 63 */
  uint8_t icon_pic[63];   /** Bitmap data in sprite format */
  uint8_t dos_file_type;  /** 0x80 + dos_file_type_t, bit 6 = 1 Write Protect */
  geos_file_type_t geos_file_type; /** 1 - 15 */
  file_structure_t file_structure; /** SEQ or VLIR */
  uint16_t file_start; /** Start address in memory for loading the program */
  uint16_t file_end;   /** End address in memory for loading the program */
  uint16_t init_prog;  /** Address pf initialization routine to call after
                          loading  the program */
  char file_name[19];  /** 19 bytes ASCII application filename. Byte 0-11 = the
                        * name padded with spaces; 12-15=version string "V1.3";
                        * 16-20 = 0's */
  uint8_t c128_flags;  /** 1 byte, flags to indicate if this program will run
                        * under the C128 OS in 40 column and in 80 column. These
                        * flags are valid for applications, desk accessories, and
                        * auto-exec files. Bit 7: zero if runs in 40 column. Bit
                        * 6: one if runs in 80 column. */
  char par_disk_or_author[20]; /** If data file, 20 bytes ASCII filename of
                                * parent's application disk. if application
                                * program, holds name of software desginer. */
  char par_application[20];    /** If data file, 20 bytes parent application
                                * filename. Byte 0-11=name padded    with spaces;
                                * 12-15=version string "V1.3"; 16-20 = 0's */
  char application_use[23];    /** 23 bytes for application use */
  char notes[96]; /** Used for file menu option getInfo. String must be null
                   * terminated and must be first char if string is empty */
} file_header_t;

_Static_assert(sizeof(file_header_t) == 254,
               "Illegal size of net_file_header_t");

typedef struct file_header_block { /** GEOS file header structure */
  tr_se_pair_t block_chain; /** Alyways 0/0xff: indicates last block, last used
                               bytes at 0xff */
  file_header_t h;
} file_header_block_t;

_Static_assert(sizeof(file_header_block_t) == 256,
               "Illegal size of file_header_t");

typedef struct icon_table_entry {
  uint8_t *graphic_data;
  uint8_t left;
  uint8_t top;
  uint8_t width;
  uint8_t height;
  vector service_routine;
} icon_table_entry_t;

typedef struct icon_table {
  uint8_t num_icons;
  uint16_t mouse_x;
  uint8_t mouse_y;
  icon_table_entry_t icons[];
} icon_table_t;

typedef struct menu_tab menu_tab_t;
typedef struct menu_item menu_item_t;

struct menu_item {
  char *text;
  uint8_t action_type;
  union {
    vector handler_function;
    menu_tab_t *sub_menu;
  };
};

struct menu_tab {
  char top;
  char bot;
  uint16_t left;
  uint16_t right;
  uint8_t menu_type_and_count;
  menu_item_t items[];
};

struct init_tab {   /** use struct inittab mytab[n] for initram              */
  uint8_t *ptr;     /** ptr to 1st byte                                      */
  uint8_t count;    /** number of following bytes                            */
  uint8_t values[]; /** actual string of bytes                               */
};

typedef struct icon_pic { /** icon/encoded bitmap description          */
  uint8_t *pic_ptr;       /** ptr to a photo scrap (or encoded bitmap) */
  uint8_t card_left;      /** position in cards (*8 pixels)            */
  uint8_t top;            /** in pixel */
  uint8_t card_width;     /** in cards                                 */
  uint8_t heigth;         /** in lines (pixels)                        */
} icon_pic_t;

typedef struct font_desc { /** describes font               */
  uint8_t baseline;
  uint8_t width;
  uint8_t height;
  uint8_t *index_tbl;
  uint8_t *data_ptr;
} font_desc_t;

typedef struct mobpos {
  uint8_t x;
  uint8_t y;
} mobpos_t;

#ifdef __cplusplus
extern "C" {
#endif

#endif
