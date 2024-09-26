/***********************************************************************
 * geos_constants.h
 *
 * This file contains #defines for use in GEOS applications
 * with llvm-mos C compiler.
 *
 * Transcribed from geoProgrammer manual by DiSc.
 *
 ***********************************************************************/

#ifndef GEOS_CONSTANTS_H
#define GEOS_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 * Miscellaneous defines
 ***********************************************************************/

#include <stdbool.h>
#include <stdint.h>

// #define LOW_BYTE(x) (*((unsigned char *)&(##x) + 0))
// #define HIGH_BYTE(x) (*((unsigned char *)&(##x) + 1))

#define WORD(w) (w & 0xff), (w >> 8)

#define STRINGIFY_AUX(x) #x
#define STRINGIFY(x) STRINGIFY_AUX(x)


/***********************************************************************
 * Hardware related defines
 ***********************************************************************/

/** values for CPU_DATA - C64 memory config */

#define RAM_64K 0x30        /** 64K RAM */
#define IO_IN 0x35          /** 60K RAM, 4K I/O space in */
#define KRNL_IO_IN 0x36     /** kernal and I/O mapped into memory */
#define KRNL_BAS_IO_IN 0x37 /** kernal, I/O and basic mapped into memory */

/** values for config - C128 mmu */

#define CIOIN 0x7E        /** 60K RAM, 4K I/O space in */
#define CRAM64K 0x7F      /** 64K RAM */
#define CKRNLBASIOIN 0x40 /** kernal, I/O and basic ROM's mapped into memory   \
                           */
#define CKRNLIOIN 0x4E    /** Kernal ROM and I/O space mapped in */

/***********************************************************************
 * Menu Equates
 ***********************************************************************/

/** Menu types */
typedef enum {
  HORIZONTAL = 0b00000000,
  VERTICAL = 0b10000000,
  CONSTRAINED = 0b01000000,
  UN_CONSTRAINED = 0b00000000
} menu_type_t;

/** Offsets to variables in the menu structure */
#define OFF_MY_TOP 0      /** offset to y pos of top of menu */
#define OFF_MY_BOT 1      /** offset to y pos of bottom of menu */
#define OFF_MX_LEFT 2     /** offset to x pos of left side of menu */
#define OFF_MX_RIGHT 4    /** offset to x pos of right side of menu */
#define OFF_NUM_M_ITEMS 6 /** offset to Alignment|Movement|Number of items */
#define OFF_1ST_M_ITEM 7  /** offset to record for 1st menu item in structure  \
                           */

/** Types of menu actions */
typedef enum {
  MENU_ACTION = 0x00,  /** for setting byte in menu table that indicates */
  DYN_SUB_MENU = 0x40, /** whether the menu item causes action */
  SUB_MENU = 0x80      /** or sub menu */
} menu_action_t;

/***********************************************************************
 * Process Related Equates
 ***********************************************************************/

/** Possible values for processFlags */

#define SET_RUNABLE 0b10000000 /** runable flag */
#define SET_BLOCKED 0b01000000 /** process blocked flag */
#define SET_FROZEN 0b00100000  /** process frozen flag */
#define SET_NOTIMER 0b00010000 /** not a timed process flag */

#define RUNABLE_BIT 7 /** runable flag */
#define BLOCKED_BIT 6 /** process blocked flag */
#define FROZEN_BIT 5  /** process frozen flag */
#define NOTIMER_BIT 4 /** not a timed process flag */

/***********************************************************************
 * Text Equates
 ***********************************************************************/

/** Bit flags in mode */

#define SET_UNDERLINE 0b10000000
#define SET_BOLD 0b01000000
#define SET_REVERSE 0b00100000
#define SET_ITALIC 0b00010000
#define SET_OUTLINE 0b00001000
#define SET_SUPERSCRIPT 0b00000100
#define SET_SUBSCRIPT 0b00000010
#define SET_PLAINTEXT 0b00000000

#define UNDERLINE_BIT 7
#define BOLD_BIT 6
#define REVERSE_BIT 5
#define ITALIC_BIT 4
#define OUTLINE_BIT 3
#define SUPERSCRIPT_BIT 2
#define SUBSCRIPT_BIT 1

/** Putchar constants */

#define EOF 0       /** end of text object */
#define BACKSPACE 8 /** move left a card */
#define TAB 9
#define FORWARDSPACE 9  /** move right one card */
#define LF 10           /** move down a card row */
#define HOME 11         /** move to top left corner of screen */
#define UPLINE 12       /** move up a card line */
#define PAGE_BREAK 12   /** page break */
#define CR 13           /** move to beginning of next card row */
#define ULINEON 14      /** turn on underlining */
#define ULINEOFF 15     /** turn off underlining */
#define ESC_GRAPHICS 16 /** escape code for grahics string */
#define ESC_RULER 17    /** ruler escape */
#define REV_ON 18       /** turn on reverse video */
#define REV_OFF 19      /** turn off reverse video */
#define GOTOX 20        /** use next byte as 1+x cursor */
#define GOTOY 21        /** use next byte as 1+y cursor */
#define GOTOXY 22       /** use next bytes as 1+x and 1+y cursor */
#define NEWCARDSET 23   /** use next 2 bytes as new font id */
#define BOLDON 24       /** turn on BOLD characters */
#define ITALICON 25     /** turn on ITALIC characters */
#define OUTLINEON 26    /** turn on OUTLINE characters */
#define PLAINTEXT 27    /** plain text mode */
#define USELAST 127     /** erase character */
#define SHORTCUT 128    /** shortcut character */

/***********************************************************************
 * Keyboard Equates
 ***********************************************************************/

#define KEY_INVALID 31
#define KEY_F1 1
#define KEY_F2 2
#define KEY_F3 3
#define KEY_F4 4
#define KEY_F5 5
#define KEY_F6 6
#define KEY_NOSCRL 7
#define KEY_TAB 9
#define KEY_LF 10
#define KEY_ENTER 11
#define KEY_F7 14
#define KEY_F8 15
#define KEY_UP 16
#define KEY_DOWN 17
#define KEY_HOME 18
#define KEY_CLEAR 19
#define KEY_LARROW 20
#define KEY_UPARROR 21
#define KEY_STOP 22
#define KEY_RUN 23
#define KEY_BPS 24
#define KEY_LEFT BACKSPACE
#define KEY_HELP 25
#define KEY_ALT 26
#define KEY_ESC 27
#define KEY_RIGHT 30
#define KEY_DELETE 29
#define KEY_INSERT 28

/***********************************************************************
 * Mouse Equates
 ***********************************************************************/

/** Bit flags for mouseOn variable */

#define SET_MSE_ON 0b10000000
#define SET_MENUON 0b01000000
#define SET_ICONSON 0b00100000

#define MOUSEON_BIT 7
#define MENUON_BIT 6
#define ICONSON_BIT 5

/***********************************************************************
 * Graphics/Screen Equates
 ***********************************************************************/

/** Constants for screen size */

#define SC_BYTE_WIDTH 40  /** width of screen in bytes */
#define SC_PIX_HEIGHT 200 /** width of screen in pixels */

#define SC_PIX_WIDTH 320 /** height of screen in scanlines */
#define SC_SIZE 8000     /** size of screen memory in bytes */

/** 128 screen size constants */

#define SCREENBYTEWIDTH 80   /** width of screen in bytes */
#define SCREENPIXELWIDTH 640 /** width of screen in pixels */

/** Bits used to set displayBufferOn flag (controls which screens get written
 * to)
 */

#define ST_WR_FORE 0x80   /** write to foreground */
#define ST_WR_BACK 0x40   /** write to background */
#define ST_WRGS_FORE 0x20 /** graphic strings only write to foreground */

/** Values for graphics strings */

#define MOVEPENTO 1     /** move pen to x,y */
#define LINETO 2        /** draw line to x,y */
#define RECTANGLETO 3   /** draw rectangle to x,y */
#define NEWPATTERN 5    /** set a new pattern */
#define ESC_PUTSTRING 6 /** start putstring interpretation */
#define FRAME_RECTO 7   /** draw frame of rectangle */
#define PEN_X_DELTA 8   /** move pen to signed word delta in x */
#define PEN_Y_DELTA 9   /** move pen to signed word delta in y */
#define PEN_XY_DELTA 10 /** move pen to signed word delta in x,y */

/** Screen colors */

#define BLACK 0
#define WHITE 1
#define RED 2
#define CYAN 3
#define PURPLE 4
#define GREEN 5
#define BLUE 6
#define YELLOW 7
#define ORANGE 8
#define BROWN 9
#define LTRED 10
#define DKGREY 11
#define GREY 12
#define MEDGREY 12
#define LTGREEN 13
#define LTBLUE 14
#define LTGREY 15

/** Values for PutDecimal calls */

#define SET_LEFTJUST 0b10000000   /** left justified */
#define SET_RIGHTJUST 0b00000000  /** right justified */
#define SET_SURPRESS 0b01000000   /** no leading 0's */
#define SET_NOSURPRESS 0b00000000 /** leading 0's */

/***********************************************************************
 * Menu Equates
 ***********************************************************************/

/** These equates are bit values for iconSelFlag that determine how an icon
 * selection is indicated to the user. If ST_FLASH is set, ST_INVERT is
 * ineffective. */

#define ST_FLASH 0x80  /** bit to indicate icon should flash */
#define ST_INVERT 0x40 /** bit to indicate icon should be inverted */

/** offset into the icon structure */

#define OFF_NM_ICNS 0   /** number of icons in structure */
#define OFF_IC_XMOUSE 1 /** mouse x start position */
#define OFF_IC_YMOUSE 3 /** mouse y start position */

/** Offsets into an icon record in icon structure */

#define OFF_PIC_ICON 0    /** picture pointer for icon */
#define OFF_X_ICON_POS 2  /** x position of icon */
#define OFF_Y_ICON_POS 3  /** y position of icon */
#define OFF_WDTH_ICON 4   /** width of icon */
#define OFF_HEIGHT_ICON 5 /** height of icon */
#define OFF_SRV_RT_ICON 6 /** pointer to service routine for icon */
#define OFF_NX_ICON 8     /** next icon in icon structure */

/***********************************************************************
 * Flag Equates
 ***********************************************************************/

/** Values for pressFlag variable */

#define KEYPRESS_BIT 7 /** other keypress */
#define INPUT_BIT 6    /** input device change */
#define MOUSE_BIT 5    /** mouse press */

#define SET_KEYPRESS 0b10000000 /** other keypress */
#define SET_INPUTCHG 0b01000000 /** input device change */
#define SET_MOUSE 0b00100000    /** mouse press */

/** values for faultFlag variable */

#define OFFTOP_BIT 7    /** mouse fault up */
#define OFFBOTTOM_BIT 6 /** mouse fault down */
#define OFFLEFT_BIT 5   /** mouse fault left */
#define OFFRIGHT_BIT 4  /** mouse fault right */
#define OFFMENU_BIT 3   /** menu fault */

#define SET_OFFTOP 0b10000000    /** mouse fault up */
#define SET_OFFBOTTOM 0b01000000 /** mouse fault down */
#define SET_OFFLEFT 0b00100000   /** mouse fault left */
#define SET_OFFRIGHT 0b00010000  /** mouse fault right */
#define SET_OFFMENU 0b00001000   /** menu fault */

#define ANY_FAULT 0b11110000

/***********************************************************************
 * GEOS File Type Equates
 ***********************************************************************/

typedef enum {
  NOT_GEOS = 0, /** Old C-64 file, without GEOS header
                 * (PRG, SEQ, USR, REL) */

  /** The following are GEOS file types reserved for compatibility
   * with old C64 files, that have simply had a GEOS header placed
   * on them. Users should be able to double click on files of
   * type BASIC and ASSEMBLY, whereupon they will be fast-loaded
   * and executed from under BASIC. */

  BASIC = 1,    /** C-64 BASIC program, with a GEOS header
                 * attached. (Commodore file type PRG.)
                 * Tp be used on programs that
                 * were executed before GEOS with:
                 *    LOAD "FILE",8
                 *    RUN
                 */
  ASSEMBLY = 2, /** C-64 ASSEMBLY program, with a GEOS header
                 * attached. (Commodore file type PRG.)
                 * Tp be used on programs that
                 * were executed before GEOS with:
                 *    LOAD "FILE",8,1
                 *    SYS(Start Address)
                 */
  DATA = 3,     /** Non-executable DATA file (PRG,SEQ, or USR)
                 * with a GEOS header attached for icon & notes
                 * ability. */

  /** The following are file types for GEOS applications & system use:
   * ALL files having one of these GEOS file types should be of
   * Commodore file type USR.
   */

  SYSTEM = 4,        /** GEOS system file */
  DESK_ACC = 5,      /** GEOS desk accessory file */
  APPLICATION = 6,   /** GEOS application file */
  APPL_DATA = 7,     /** data file for a GEOS application */
  FONT = 8,          /** GEOS font file */
  PRINTER = 9,       /** GEOS printer driver */
  INPUT_DEVICE = 10, /** INPUT device (mouse, etc.) */
  DISK_DEVICE = 11,  /** DISK device driver */
  SYSTEM_BOOT = 12,  /** GEOS system boot file (for GEOS, GEOS BOOT,
                        GEOS KERNAL) */
  TEMPORARY = 13,    /** Temporary file type, for swap files.
                      * The Desktop will automatically delete all
                      * files of this type upon opening a disk. */
  AUTO_EXEC = 14,    /** Applications automatically be loaded & run
                      * just after booting but before Desktop runs. */
  INPUT_128 = 15,    /** 128 Input driver */

  NUMFILETYPES = 16
} geos_file_type_t;

/** GEOS file structure types. Each "structure type" specifies the organization
 * of data blocks on the disk, and has nothing to do with the data in the
 * blocks. */

typedef enum {
  SEQUENTIAL, /** standard T,S structure (like commodore SEQ
               * and PRG files) */
  VLIR        /** Variable-length-indexed-record-file (user for
               * Fonts, Documents & some programs)
               * This is GEOS only format. */
} file_structure_t;

/** Standard Commodore file types (supported by the old 1541 DOS) */
typedef enum {
  DEL, /** deleted file */
  SEQ, /** sequential file */
  PRG, /** program file */
  USR, /** user file */
  REL, /** relative file */
  CBM  /** cbm bam protection file, currently only on
        * 1581 disk drivers. User to protect specific
        * blocks/tracks from collection at validation
        * time */
} dos_file_type_t;

#define TOTAL_BLOCKS                                                           \
  664 /** number of blocks on disk, not including                              \
       * directory track. */

/***********************************************************************
 * Director Header Equates
 ***********************************************************************/

/** Offsets into directory header structure */

#define OFF_TO_BAM 4      /** first BAM entry */
#define OFF_DISK_NAME 144 /** disk name string */
#define OFF_OP_TR_SC                                                           \
  171                 /** track and sector for off page directory              \
                       * entries. 8 files may be moved off page. */
#define OFF_GS_ID 173 /** where GEOS ID string is located */
#define OFF_GS_DTYPE                                                           \
  189 /** GEOS disk type. Currently, is 0 for                                  \
       * normal disk, 'B' for BOOT disk. Zeroed                                \
       * on destination disk during disk copy. */

/***********************************************************************
 * Directory Entry Equates
 ***********************************************************************/

#define ST_WR_PR                                                               \
  0x40 /** write protect bit: bit 6 of byte 0 in the                           \
        * directory entry */

/** Offsets within a specific file´s Directory Entry. */

#define OFF_CFILE_TYPE 0   /** standard commodore file type indicator */
#define OFF_INDEX_PTR 1    /** index table pointer (VLIR file) */
#define OFF_DE_TR_SC 1     /** track for file´s 1st data block */
#define OFF_FNAME 3        /** file name */
#define OFF_GHDR_PTR 19    /** track/sector info on where header block is */
#define OFF_GSTRUC_TYPE 21 /** GEOS file structure type */
#define OFF_GFILE_TYPE 22  /** geos file type indicator */
#define OFF_YEAR 23        /** year (first byte of date stamp) */
#define OFF_SIZE 28        /** size of file in blocks */
#define OFF_NXT_FILE 32    /** next file entry in directory structure */

/** Offsets into a directory block */

#define FRST_FILE_ENTRY 2 /** first dir entry is at byte #2 */

/***********************************************************************
 * File Header Equates
 ***********************************************************************/

/** offsets into GEOS file header block */

#define O_GHIC_WIDTH 2   /** byte: width in bytes of file icon */
#define O_GHIC_HEIGHT 3  /** byte: indicates height of file icon */
#define O_GHIC_PIC 4     /** 64 bytes: picture data for file icon */
#define O_GHCMDR_TYPE 68 /** byte: Comm. file type */
#define O_GHGEOS_TYPE 69 /** byte: GEOS file type */
#define O_GHSTR_TYPE 70  /** byte: GEOS file structure type */
#define O_GHST_ADDR 71   /** 2 bytes: start address of file in mem */
#define O_GHEND_ADDR 73  /** 2 bytes: end address of file on memory */
#define O_GHST_VEC 75    /** 2 bytes: init vector if file is appl. */
#define O_GHFNAME 77     /** 20 bytes, permanent file name */

#define O_128_FLAGS                                                            \
  96                   /** 1 byte, flag to indicate if this program            \
                        * will run under the C128 PS in 40 column and          \
                        * in 80 column. These flags are valid for              \
                        * applications, desk accessories, and auto-exec        \
                        * files. But 7: zero if runs in 40 column.             \
                        * Bit 6: one if runs in 80 column.                     \
                        */
#define O_GH_AUTHOR 97 /** 20 bytes: author´s name (only if is applic.) */
#define O_GHINFO_TXT                                                           \
  0xa0 /** offset to notes that are stored with the file                       \
        * and edited in the deskTop "get info" box. */

/** if file is an application data file: */

#define O_GHP_DISK 97 /** 20 bytes: disk name of parent application´s disk */
#define O_GHP_FNAME                                                            \
  117 /** 20 bytes: permanent filename of parent application                   \
       */

/***********************************************************************
 * GetFile  Equates
 ***********************************************************************/

/** The following equates define file loading options for several of the
 * GEOS file handling routines like GetFile. These bit definitions are used to
 * set the RAM variable loadOpt. */

#define ST_LD_AT_ADDR                                                          \
  0x01 /** "Load At Address": Load file a called                               \
        * specified address instead of address file was                        \
        * saved from. */
#define ST_LD_DATA                                                             \
  0x80 /** "Load Datafile": Used when application                              \
        * datafile is opened from deskTop. Used to                             \
        * indicate to application that r2 and r3                               \
        * contains information about where to                                  \
        * find the selected datafile. */
#define ST_PR_DATA                                                             \
  0x40 /** "Print Datafile": Used when application                             \
        * datafile is selected for printing from deskTop.                      \
        * Used to indicate to application that r2 and r3                       \
        * contains information about where to find the                         \
        * selected datafile. */

/***********************************************************************
 * Disk Equates
 ***********************************************************************/

#define DK_NM_ID_LEN 18 /** # of characters in disk name */

/** Equates for variable "driveType". High two bits of driveType have special
 * meaning (only 1 may be set):
 *   Bit 7: if 1, then RAM DISK
 *   Bit 6: if 1, then Shadowed disk
 */

#define DRV_NULL 0     /** No drive present at this device address */
#define DRV_1541 1     /** Drive type Commodore 1541 */
#define DRV_1571 2     /** Drive type Commodore 1571 */
#define DRV_1581 3     /** Drive type Commodore 1581 */
#define DRV_NETWORK 15 /** Drive type for GEOS getNet "drive" */

/** Constants used by low-level GEOS disk handling routines */

#define N_TRACKS 35  /** # of tracks available on the 1541 disk */
#define DIR_TRACK 18 /** track # reserved on disk for directory */
#define DIR_1581_TRACK                                                         \
  40 /** track # reserved on disk for directory on a 1581                      \
      */

/** Disk access commands */

#define MAX_CMND_STR 32 /** maximum length a command string would have */
#define DIR_ACC_CHAN 13 /** default direct access channel */
#define REL_FILE_NUM                                                           \
  9 /** logical file number & channel used for relative files. */
#define CMND_FILE_NUM                                                          \
  15 /** logical file number & channel used for command files. */

/** Index to a command buffer for setting the track and sector number for a
 * direct access command */

#define TRACK 9   /** offset to low byte decimal ASCII track number */
#define SECTOR 12 /** offset to low byte decimal ASCII sector number */

/***********************************************************************
 * Disk Error Equates
 ***********************************************************************/

/** The following equates are ERROR values returned from direct access routines
 */
typedef enum {
  NO_BLOCKS = 1,         /** "not enough blocks" */
  INV_TRACK = 2,         /** "invalid track" */
  INSUFF_SPACE = 3,      /** "not enough blocks on disk" */
  FULL_DIRECTORY = 4,    /** "directory full" */
  FILE_NOT_FOUND = 5,    /** "file not found" */
  BAD_BAM = 6,           /** "bad Block Availability Map" */
  UNOPENED_VLIR = 7,     /** "unopened VLIR file" */
  INV_RECORD = 8,        /** "invalid record" */
  OUT_OF_RECORDS = 9,    /** "cannot insert/append more records" */
  STRUCT_MISMAT = 10,    /** "file structure mismatch" */
  BFR_OVERFLOW = 11,     /** "buffer overflow during load" */
  CANCEL_ERR = 12,       /** "deliberate cancel error" */
  DEV_NOT_FOUND = 13,    /** "device not found" */
  INCOMPATIBLE = 14,     /** This error is returned when an attempt is made
                          * to load a program that can't be run on the
                          * current graphics modes under the C-128 GEOS. */
  HDR_NOT_THERE = 0x20,  /** "cannot find file header block" */
  NO_SYNC = 0x21,        /** "can't find sync mark on disk" */
  DBLK_NOT_THERE = 0x22, /** "data block not present" */
  DAT_CHKSUM_ERR = 0x23, /** "data block checksum error" */
  WR_VER_ERR = 0x25,     /** "write verify error" */
  WR_PR_ON = 0x26,       /** "disk is write protected" */
  HDR_CHKSUM_ERR = 0x27, /** "checksum error in header block" */
  DSK_ID_MISMAT = 0x29,  /** "disk ID mismatch" */
  BYTE_DEC_ERR = 0x2e,   /** "can't decode flux transitions off of disk" */
  DOS_MISMATCH = 0x73    /** "wrong dos indicator on disk" */
} disk_err_t;

/***********************************************************************
 * Dialog Box Equates
 ***********************************************************************/

#define DEF_DB_POS 0x80 /** command for default dialog box position */
#define SET_DB_POS 0    /** command for user-set DB position */

/** Doalog box descriptor table commands */

#define OK                                                                     \
  1                /** Put up system Icon for "OK", command is                 \
                    * followed by 2 byte position indicator, x pos.            \
                    * in bytes, y pos. in pixels. NOTE: positions              \
                    * are offsets from the top left corner of the              \
                    * dialog box. */
#define CANCEL 2   /** Like OK, system DB icon, position follows */
#define YES 3      /** Like OK, system DB icon, position follows */
#define NO 4       /** Like OK, system DB icon, position follows */
#define OPEN 5     /** Like OK, system DB icon, position follows */
#define DISK 6     /** Like OK, system DB icon, position follows */
#define FUTURE1 7  /** reserved for future system icons */
#define FUTURE2 8  /** reserved for future system icons */
#define FUTURE3 9  /** reserved for future system icons */
#define FUTURE4 10 /** reserved for future system icons */

/** More dialog box descriptor table commands */

#define DBTXTSTR 11    /** Command to display a text string. */
#define DBVARSTR 12    /** Used to put out variant string. */
#define DBGETSTRING 13 /** Get an ASCII string from the user. */
#define DBSYSOPV 14    /** Any press not over an icon return to applic. */
#define DBGRPHSTR 15   /** Execute graphics string. */
#define DBGETFILES 16  /** Get filename from user. */
#define DBOPVEC 17     /** User defined other press vector. */
#define DBUSRICON 18   /** User defined icon. */
#define DB_USR_ROUT 19 /** User defined routine. */

/** The following equates are used to specify offsets into a dialog box
 * desciptor table */
#define OFF_DB_FORM 0   /** box form description, i.e. shadow or not */
#define OFF_DB_TOP 1    /** position for top of dialog box */
#define OFF_DB_BOT 2    /** position for bottom of dialog box */
#define OFF_DB_LEFT 3   /** position for left of dialog box */
#define OFF_DB_RIGHT 5  /** position for right of dialog box */
#define OFF_DB_1STCMD 7 /** 1st command in dialog box descriptor table */

/** The following equates speccify the dimensions of the system defined dialog
 * box icons. */

#define SYSDBI_WIDTH 6   /** height in pixels */
#define SYSDBI_HEIGHT 16 /** width in bytes */

/** These equates define a standard, default, dialog box position and
 * size as well as some standard positions within the box for outputting
 * text and icons. */

#define DEF_DB_TOP 32    /** top y coordinate of default box */
#define DEF_DB_BOT 127   /** bottom y coordinate of default box */
#define DEF_DB_LEFT 64   /** left edge of default box */
#define DEF_DB_RIGHT 255 /** right edge of default box */

#define TXT_LN_X 16 /** standard text x start */

#define TXT_LN_1_Y 16 /** standard text line y offsets */
#define TXT_LN_2_Y 32
#define TXT_LN_3_Y 48
#define TXT_LN_4_Y 64
#define TXT_LN_5_Y 80

/** byte offsets to... */

#define DBI_X_0 1  /** left side standard icon x position */
#define DBI_X_1 9  /** center standard icon x position */
#define DBI_X_2 17 /** right side standard icon x position */
#define DBI_Y_0 8  /** left side standard icon y position */
#define DBI_Y_1 40 /** center standard icon y position */
#define DBI_Y_2 72 /** right side standard icon y position */

/***********************************************************************
 * Defines for DoDlgBox
 ***********************************************************************/

#define DB_NAME(name)                                                          \
  extern uint8_t name[];                                                       \
  asm(".type " STRINGIFY(name) ",@object\n.section .data." STRINGIFY(          \
      name) ",\"aw\",@progbits\n" STRINGIFY(name) ":");
#define DB_NAME_SECT(name, sect)                                               \
  extern uint8_t name[];                                                       \
  asm(".type " STRINGIFY(name) ",@object\n.section ." STRINGIFY(               \
      sect) "." STRINGIFY(name) ",\"aw\",@progbits\n" STRINGIFY(name) ":");
#define DB_END(name)                                                           \
  asm(".byte 0\n.size " STRINGIFY(name) ", . - " STRINGIFY(name));
#define DB_DEFPOS(pattern) asm(".byte 0x80|" STRINGIFY(pattern));
#define DB_SETPOS(pattern, top, bottom, left, right)                              \
  asm(".byte " STRINGIFY(pattern) "\n.byte " STRINGIFY(                           \
      top) "\n.byte " STRINGIFY(bottom) "\n.word " STRINGIFY(left) "\n."          \
                                                                   "word"         \
                                                                   " " STRINGIFY( \
                                                                       right));
#define DB_ICON(icon, x, y)                                                    \
  asm(".byte " STRINGIFY(icon) "\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(y));
#define DB_TXTSTR(x, y, text)                                                  \
  asm(".byte 11\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(                    \
      y) "\n.short " STRINGIFY(text));
#define DB_VARSTR(x, y, zp_ptr)                                                \
  asm(".byte 12\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(                    \
      y) "\n.byte " STRINGIFY(zp_ptr));
#define DB_GETSTR(x, y, zp_ptr, length)                                        \
  asm(".byte 13\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(                    \
      y) "\n.byte " STRINGIFY(zp_ptr) "\n.byte " STRINGIFY(length));
#define DB_SYSOPV() asm(".byte 14");
#define DB_GRPHSTR(ptr) asm(".byte 15\n.short " STRINGIFY(ptr));
#define DB_GETFILES(x, y)                                                      \
  asm(".byte 16\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(y));
#define DB_OPVEC(ptr) asm(".byte 17\n.short " STRINGIFY(ptr));
#define DB_USRICON(x, y, icon_ptr)                                             \
  asm(".byte 18\n.byte " STRINGIFY(x) "\n.byte " STRINGIFY(                    \
      y) "\n.short " STRINGIFY(icon_ptr));
#define DB_USRROUT(ptr) asm(".byte 19\n.short " STRINGIFY(ptr));

/***********************************************************************
 * VIC Chip Equates
 ***********************************************************************/

#define GRBANK0 0b11 /** bits indicate VIC ram is 0x0000-0x3fff, 1st 16K */
#define GRBANK1 0b10 /** bits indicate VIC ram is 0x4000-0x7fff, 2nd 16K */
#define GRBANK2 0b01 /** bits indicate VIC ram is 0x8000-0xbfff, 3rd 16K */
#define GRBANK3 0b00 /** bits indicate VIC ram is 0xc000-0xffff, 4th 16K */

#define MOUSE_SPRNUM 0 /** sprite no. used for mouse (used to set VIC) */

#define VIC_YPOS_OFF                                                           \
  50 /** Position offset from 0 to position a                                  \
      * hardware sprite at the top of the screen.                              \
      * Used to map from GEOS coordinates to hardware                          \
      * position coordinates. */

#define VIC_XPOS_OFF                                                           \
  24 /** As above, offset from hardware 0 position to left                     \
      * of screen, used to map GEOS coordinates in VIC. */

#define ALARMMASK                                                              \
  0b00000100 /** mask for the alarm bit in the CIA chip                        \
              * interrupt control register. */

/** Desk Accessoriy save foreground bit. */

#define FG_SAVE 0b10000000  /** save and restore foreground graphics data. */
#define CLR_SAVE 0b01000000 /** save and restore color information. */

/***********************************************************************
 * C128 640 support
 ***********************************************************************/
#define ADD1_W 0x2000
#define ADD1_B 0x20
#define DOUBLE_W 0x8000
#define DOUBLE_B 0x80

/***********************************************************************
 * C128 bsw128
 ***********************************************************************/
#define ARROW 0    /** pass this to SetMsePic */
#define GR_40 0    /** use these two to test */
#define GR_80 0x80 /** graphMode             */

/***********************************************************************
 * Unknown
 ***********************************************************************/

#define CLICK_COUNT 30
#define DISK_DRV_LGH 0x0d80
#define OS_VARS_LGH 0x0500

#ifdef __cplusplus
}
#endif

#endif
