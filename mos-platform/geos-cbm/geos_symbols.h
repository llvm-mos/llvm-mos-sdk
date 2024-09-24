/***********************************************************************
 * geos_symbols.h
 *
 * This file contains symbol definitions for use in GEOS applications
 * with llvm-mos C compiler.
 *
 * Transcribed from geoProgrammer manual by DiSc.
 *
 ***********************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "geos_types.h"

/***********************************************************************
 * Zero Page Equates and Space Definintions
 ***********************************************************************/

extern volatile uint8_t CPU_DDR;
extern volatile uint8_t CPU_DATA;
extern uint8_t STATUS;
extern uint8_t curDevice;

/** zero page variable definitions: */

extern uint8_t *zpage; /** 6510 registers: CPU_DDR and CPU_DATA */

extern uint16_t __zp __r0;
extern uint16_t __zp __r1;
extern uint16_t __zp __r2;
extern uint16_t __zp __r3;
extern uint16_t __zp __r4;
extern uint16_t __zp __r5;
extern uint16_t __zp __r6;
extern uint16_t __zp __r7;
extern uint16_t __zp __r8;
extern uint16_t __zp __r9;
extern uint16_t __zp __r10;
extern uint16_t __zp __r11;
extern uint16_t __zp __r12;
extern uint16_t __zp __r13;
extern uint16_t __zp __r14;
extern uint16_t __zp __r15;

/** The following variables are saved by GEOS during dialog boxes and desk
 * accessories */

extern uint16_t curPattern; /** pointer to current pattern */
extern uint8_t *string;
extern uint8_t
    baselineOffset; /** Offset from top line to baseline in character set */
extern uint16_t curSetWidth;     /** Card with in pixels */
extern uint8_t curHeight;        /** Card height in pixels */
extern uint16_t curIndexTable[]; /** Size of each card in bytes */
extern uint8_t *cardDataPntr;    /** Pointer to the actual card graphics data */
extern uint8_t currentMode;  /** Current underline, italc and reverse flags */
extern uint8_t dispBufferOn; /** bit 7 controls writes to FG screen
                              * bit 6 controls writes to background screen */
extern uint8_t mouseOn;      /** flag indicating that the mouse mode is on */
extern uint8_t *msePicPtr;   /** pointer to mouse graphic data */
extern uint8_t windowTop;    /** top line of window for text clipping */
extern uint8_t windowBottom; /** bottom line of window for text clipping */
extern uint16_t leftMargin;  /** leftmost point for writing characters.
                              * CR will return to this point */
extern uint16_t rightMargin; /** rightmost point for writing characters. When
                              * crossed, call mode through StringFaultVector */

/** End of variables saved during DB's and DA's */

extern uint8_t pressFlag; /** Flag indicating that a new key has been pressed */
extern uint16_t mouseXPos;     /** x position of mouse */
extern uint8_t mouseYPos;      /** y position of mouse */
extern uint8_t *returnAddress; /** address to return from in-line call */

extern uint8_t graphMode;
extern uint8_t TURBO_DD00;     /** from 1541 turbo */
extern uint8_t TURBO_DD00_CPY; /** from 1541 turbo */

/** equates to access low and high bytes of general purpose registers: */

extern uint8_t __zp __r0L;
extern uint8_t __zp __r0H;
extern uint8_t __zp __r1L;
extern uint8_t __zp __r1H;
extern uint8_t __zp __r2L;
extern uint8_t __zp __r2H;
extern uint8_t __zp __r3L;
extern uint8_t __zp __r3H;
extern uint8_t __zp __r4L;
extern uint8_t __zp __r4H;
extern uint8_t __zp __r5L;
extern uint8_t __zp __r5H;
extern uint8_t __zp __r6L;
extern uint8_t __zp __r6H;
extern uint8_t __zp __r7L;
extern uint8_t __zp __r7H;
extern uint8_t __zp __r8L;
extern uint8_t __zp __r8H;
extern uint8_t __zp __r9L;
extern uint8_t __zp __r9H;
extern uint8_t __zp __r10L;
extern uint8_t __zp __r10H;
extern uint8_t __zp __r11L;
extern uint8_t __zp __r11H;
extern uint8_t __zp __r12L;
extern uint8_t __zp __r12H;
extern uint8_t __zp __r13L;
extern uint8_t __zp __r13H;
extern uint8_t __zp __r14L;
extern uint8_t __zp __r14H;
extern uint8_t __zp __r15L;
extern uint8_t __zp __r15H;

/** Zero Page variables for use by applications ONLY! Not to be used by
 * GEOS or desk accessories
 */
extern uint16_t __zp __a0; /** free for use by application */
extern uint8_t __zp __a0L; /** free for use by application */
extern uint8_t __zp __a0H; /** free for use by application */
extern uint16_t __zp __a1; /** free for use by application */
extern uint8_t __zp __a1L; /** free for use by application */
extern uint8_t __zp __a1H; /** free for use by application */

/***********************************************************************
 * 0x0300 Area  Equates and Space Definintions
 ***********************************************************************/

extern vector bkvec;         /** break ins vector */
extern vector nmivec;        /** nmi vector */
extern vector kernalVectors; /** location of kernal vectors */

/***********************************************************************
 * 0x8000 Area  Equates and Space Definintions
 ***********************************************************************/

/** Start of GEOS system RAM */

extern disk_block_t diskBlkBuf; /** general disk block buffer */
extern file_header_t
    fileHeader; /** block used to hold file head block for a GEOS file. */
extern dir_header_t curDirHead; /** block contains directory header information
                                 * for disk in currently selected drive. */
extern file_tr_se_tab_t
    fileTrScTab; /** buffer used to hold track and sector chain for
                  * a file of maximum size 32258 bytes */
extern dir_entry_t dirEntryBuf; /** buffer user to build a directory entry */
extern disk_name_t DrACurDkNm;  /** Disk name of disk in drive A
                                 * 18 char disk name (padded with 0xa0) */
extern disk_name_t DrBCurDkNm;  /** Disk name of disk in drive B
                                 * 18 char disk name (padded with 0xa0) */
extern file_name_t
    dataFileName; /** Name of data file (passed to application) */
extern disk_name_t dataDiskName;    /** Disk that data file is on */
extern prt_drv_name_t PrntFilename; /** Name of current printer driver
                                     * 16 byte filename, 1 byte terminator */
extern disk_name_t PrntDiskName; /** Disk that current printer driver resides on
                                  * disk name plus terminator byte */
extern uint8_t curDrive;    /** currently active disk drive (8, 9, 10 or 11) */
extern uint8_t diskOpenFlg; /** indicates if a disk is currently open */
extern uint8_t isGEOS;      /** indicates if current disk is a GEOS disk */
extern uint8_t interleave;  /** BlkAlloc uses the value here as the desired
                             * interleave when selecting free blocks */
extern uint8_t numDrives;   /** # of drives running on the system */
extern uint8_t driveType;   /** Disk Drive types: 1 byte drive type for each
                             * of drives 8,9,10,11 */
extern uint8_t turboFlags;  /** Turbo stat flages for drives 8,9,10, and 11 */

/** Variables kept current for a specific opened file of structure type VLIR */

extern uint8_t curRecord;   /** current record # */
extern uint8_t usedRecords; /** number of records in open file */
extern uint8_t fileWritten; /** flag indicating if file has been written to
                             * since last update of index Tab & BAM */
extern uint16_t fileSize;   /** current size (in blocks) of file. This is
                             * pulled in from & written to directory entry */

/** The following variables are saved by GEOS during dialog boxes and desk
 * accessories */

extern vector appMain; /** Applications main loop code. Allows apps to include
                        * their own main loop at the end of OS main loop */
extern vector
    intTopVector;            /** Called at the top of OS interrupt code to allow
                              * application programs to have interrupt level routines */
extern vector intBotVector;  /** Called at the bottom of OS interrupt code */
extern vector mouseVector;   /** routine to call on mouse press */
extern vector keyVector;     /** routine to call on key press */
extern vector inputVector;   /** routine to call on device change */
extern vector mouseFaultVec; /** routine to call when mouse goes outside region
                                or off a menu */
extern vector otherPressVec; /** routine to call on mouse press that is not a
                                menu or an icon */
extern vector StringFaultVec; /** vector for when character is written over
                                 right margin */
extern vector alarmTmtVector; /** address of a service routine for the alarm
                               * clock time-out (ringing, graphic, etc.) that
                               * the App. can use if necessary. Normally 0. */

extern vector BRKVector;     /** routine called when BRK encountered */
extern vector RecoverVector; /** routine called to recover background behind
                              * menus and dialog boxes */
extern uint8_t
    selectionFlash;       /** speed at which menu items and icons are flashed */
extern uint8_t alphaFlag; /** flag for alphanumeric input */
extern uint8_t iconSelFlg;  /** indicates how to flash icons when selected */
extern uint8_t faultData;   /** Bit flags for mouse faults */
extern uint8_t menuNumber;  /** # of currently working menu */
extern uint8_t mouseTop;    /** top most position for mouse */
extern uint8_t mouseBottom; /** bottom most position for mouse */
extern uint16_t mouseLeft;  /** left most position for mouse */
extern uint16_t mouseRight; /** right most position for mouse */

/** Global variables for string input and prompt manipulation */

extern uint16_t stringX; /** X position for string input */
extern uint8_t stringY;  /** Y position for string input */

/** End of variables saved during DB's and DA's */

extern uint8_t *mousePicData; /** ram array for mouse picture data */
extern uint8_t maxMouseSpeed; /** maximum speed for mouse */
extern uint8_t minMouseSpeed; /** minimum speed for mouse */
extern uint8_t mouseAccel;    /** acceleration of mouse */
extern uint8_t keyData; /** This is where key service routines should look */
extern uint8_t
    mouseData; /** This is where mouse service routines should look */
extern uint8_t inputData; /** This is where input drivers pass device
                           * specific info to applications that want it */
extern uint8_t mouseSpeed;
extern volatile uint16_t
    random; /** random number, incremented each interrupt */
extern uint8_t
    *saveFontTab; /** when going into menus, save user active font table here */
extern uint8_t dblClickCount; /** used to determine double clicks on icons */
extern uint8_t year;
extern uint8_t month;
extern uint8_t day;
extern uint8_t hour;
extern uint8_t minutes;
extern uint8_t seconds;
extern uint8_t alarmSetFlag; /** TRUE if the alarm is set for geos to monitor */

/** dialog box variables */

extern uint8_t sysDBData;     /** used internally to indicate which command
                               * caused a return to the application (in dialog
                               * boxes). Actual data is returned in r0L. */
extern uint8_t screencolors;  /** default screen colors */
extern uint8_t *dlgBoxRamBuf; /** buffer to hold variables while DB or DA is
                               * running (to 0x8697) */

/** Second global memory area */

extern uint8_t savedmoby2;  /** Saved value of moby2 for context saving done
                             * in dlg boxes & desk accessories. Left out
                             * of original GEOS save code, put here so we
                             * don't screw up desk accessories, etc. that
                             * know the size of TOT_SRAM_SAVED above */
extern uint8_t scr80polar;  /** Copy of reg 24 in VDC for C128 */
extern uint8_t scr80colors; /** Screen colors for 80 column mode on C128.
                             * Copy of reg 24 in VDC for C128. */
extern uint8_t vdcClrMode;  /** Holds current color mode for C128 color rtns */
extern uint8_t
    driveData[4]; /** 1 byte each reserved for disk drives
                   * about each device (each driver may use differently) */
extern uint8_t ramExpSize;
extern uint8_t sysRAMFlg;
extern uint8_t firstBoot; /** This flag is changed from 0 to 0xff after deskTop
                           * comes up for the first time after booting */
extern uint8_t curType;   /** Current disk type (copied from diskType) */
extern uint8_t *ramBase;  /** RAM bank for each disk drive to use if drive type
                           * is RAM disk or Shadowed Drive. */
extern file_name_t inputDevName; /** Holds name of current input device */
extern disk_name_t DrCCurDkNm;   /** Disk name of disk in drive C
                                  * 18 char disk name (padded with 0xa0) */
extern disk_name_t DrDCurDkNm;   /** Disk name of disk in drive D
                                  * 18 char disk name (padded with 0xa0) */
extern dir_header_t dir2Head;    /** 2nd directory header block, for larger disk
                                  * capacity drives (such as 1571) */

extern uint8_t sprpic[8][64]; /** Addresses of specific sprite picture data */
extern uint8_t
    *objPointer[8]; /** Addresses of pointers to sprite object graphics */

/***********************************************************************
 * 0xc000 Area  Equates and Space Definintions
 ***********************************************************************/

extern char *bootName;      /** start of "GEOS BOOT" string */
extern uint8_t version;     /** GEOS version byte */
extern uint8_t nationality; /** nationality byte */
extern uint8_t
    sysFlgCopy; /** copy of sysRAMFlg saved here when going to BASIC */
extern uint8_t *dateCopy; /** copy of year, month, day */

/***********************************************************************
 * 0xd000 Area  VIC II graphics chip definitions and equates
 ***********************************************************************/

extern mobpos_t mobpos[8];
extern uint8_t msbxpos;
extern uint8_t grcntrl1;   /** graphics control register #1 */
extern uint8_t rasreg;     /** raster register */
extern uint8_t lpxpos;     /** light pen x position */
extern uint8_t lpypos;     /** light pen y position */
extern uint8_t mobenble;   /** moving object enable bits */
extern uint8_t grcntrl2;   /** graphics control register #2 */
extern uint8_t moby2;      /** double object size in y */
extern uint8_t grmemptr;   /** graphics memory pointer VM13-VM10|CB13-CB11 */
extern uint8_t grirq;      /** graphics chip interrupt register */
extern uint8_t grirqen;    /** graphics chip interrupt enable register */
extern uint8_t mobprior;   /** moving object to background priority */
extern uint8_t mobmcm;     /** moving object multi-color mode select */
extern uint8_t mobx2;      /** double object size in x */
extern uint8_t mobmobcol;  /** object to object collision register */
extern uint8_t mobbakcol;  /** object to background collision register */
extern uint8_t extclr;     /** exterior (border) color */
extern uint8_t bakclr[4];  /** background #0 color */
extern uint8_t mcmclr0[2]; /** multi color mode color 0 */
extern uint8_t mobclr[8];  /** object color */
extern uint8_t keyreg;
extern uint8_t clkreg;

/***********************************************************************
 * 0xf000 Area Equates
 ***********************************************************************/

extern vector NMI_VECTOR;   /** nmi vector location */
extern vector RESET_VECTOR; /** reset vector location */
extern vector IRQ_VECTOR;   /** interrupt vector location */

#ifdef __cplusplus
}
#endif
