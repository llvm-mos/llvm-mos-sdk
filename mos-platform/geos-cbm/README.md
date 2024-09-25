
# GEOS target for llvm-mos

The GEOS target allows the creation of GEOS VLIR applications. This are applications which can consist of up to 127 overlays, where code can be swapped in as needed. Currently the ˋgeos-cbmˋ target supports only up to 16 overlays but can be easily extended for more.

Nearly the complete GEOS API as described in the "Official GEOS programmer´s reference guide" and "Hitchhikers Guide to GEOS" is now available from C. Only a very few functions which do not make sense or do not work in C context were left out.

This text assumes that you are familiar with GEOS, the way applications are programmed under GEOS and the GEOS API and file formats which are described in both mentioned books. Both books can be easily found as PDF files in the internet.

# Files

You find all the GEOS files that you need to build in the `.../mos-platform/geos-cbm` directory. In a standard installation on Linux you find the mos-platform directory under `/usr/local`.

## Include Files

To code for GEOS you have to include the GEOS header file:

    #include <geos.h>

This header file itself includes a few more header files. Most of the definitions are taken from geoProgrammer disc:

| File | Description |
|------------------|-----------------------------------------------------|
| geos_constants.h | all the constant definitions                        |
| geos_symbols.h   | Definition of all GEOS global variables             |
| geos_types.h     | C type definitions to support easy GEOS programming |
| geos_routines.h  | C function declarations of the GEOS API             |
| geos_memorymap.h | Some memory addresses you might need                |

## Library files
The needed library files are located in `.../mos-platform/geos-cbm/lib`. They are automatically included by the `mos-geos-cbm-clang` command.

| File     | Description                                         |
| -------- | --------------------------------------------------- |
| libcrt.a | The library code for this target                    |
| vlir.ld  | Linker driver file for building the cvt output file |
| geos.ld  | Linker file with GEOS symbol values                 |
| link.ld  | Empty file, needed for compilaton tools             |

## Examples

In the llvm-mos-sdk´s example folder you find a directory geos-cbm. In that directory you find a port of the SamVlir sample application of geoProgrammer to C. Have a look at it as it shows important aspects of how to make overlays, how to l
- load code into RAM from overlay VLIR chains
- use graphic strings
- use menus
- use icons
- use dialog boxes 
- show and open GEOS Desk Accessories from GEOS menu.

# Command line

To compile a C file use the command:

    mos-geos-cbm-clang -o myapp.cvt myapp.c

This creates a GEOS convert file which contains the VLIR application (the directory entry, the info block and all VLIR code chains. To execute the application you first need to convert it to its normal format using e.g. the GEOS convert application.

A more convenient way is to use the c1541 tool from the VICE emulator. This statement creates an example d64 image and puts the myapp sample application on that disk image, automatically converting it:

    c1541 -format example,21 d64 example.d64 -geoswrite myapp.cvt -dir

For crosschecking it displays the directory. As per vice 3.8 there are 2 issues with the geoswrite command in c1541:

1. It does not show the number of allocated blocks correctly
2. It can not overwrite an already existing file on a d64 image.

# Coding hints

Some important information for successfully creating GEOS applications with the llvm-mos GEOS target follow. Please read them!

## Application info block

Every GEOS application needs an info block. If you do not supply one, a default will be included into the cvt output file by the linker.

If you want your own info block, please supply it as C code as shown here:

    __attribute__((section(".info_block")))
    retain
    file_header_t  __std_file_header  = {
    3,21, 0x80|63,
    {
	    0b11111111, 0b11111111, 0b11111111,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b10000000, 0b00000000, 0b00000001,
	    0b11111111, 0b11111111, 0b11111111,
    },
    0x80|USR,
    APPLICATION,
    VLIR,
    0x0400, 0x03ff, 0x0400,
    "Sample VLIR V1.0\000\000\000",
    0,
    "Dirk Schnorpfeil",
    "",
    "",
    "This is the llvm-mos GEOS VLIR sample application"
    };

This puts a variable `__std_file_header` in a linker section called `info_block`. The linker will pick it up from there and put it into the cvt output file. The bit constants are actually the bits of the image data of the icon of the application.

## Zero page usage

The GEOS target of llvm-mos uses zero page registers from address `0x70` to `0xfb`. The llvm-mos imaginary registers are located on `0x70` to `0x8f` (therefore `a2`-`a9` are not available in your assembler code). The remaining addresses up to 0xfb are used by the compiler to put often used global variables there.

Since the area from `0x90` to `0xfb` is also used by commodore dos routines which are called from GEOS, all GEOS API functions which might call a commodore dos routine will first back up the area from `0x90` to `0xfb` to a global buffer and restore the values before returning back to C code. As disk access is slow this will not hamper performance of you application.

If you ever need to call commodore dos functions (which you actually never should need) make sure that you follow the same pattern calling `__swap_userzp` before and after like shown here in the `OpenRecordFile` function:

    __attribute__((leaf))
    disk_err_t  OpenRecordFile(const  char*  file_name)
    {
    	disk_err_t  errno;
    	__r0 = (uint16_t)file_name;
    
    	__attribute__((leaf)) asm  volatile(
    	"jsr __swap_userzp \n"
    	"jsr __OpenRecordFile \n"
    	"jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
    	);
	    return errno;
    }

## GEOS pseudo registers

GEOS defines the pseudo registers r0 to r15 and their 8-bit variants r0L and r0H to r15L and r15H. You can access this registers where needed by putting two underscores in front of their names. They are all defined in `geos_symbols.h` like this:

    extern  uint16_t  __zp __r0;
    extern  uint16_t  __zp __r1;
    extern  uint16_t  __zp __r2;
    extern  uint16_t  __zp __r3;
    extern  uint16_t  __zp __r4;
    extern  uint16_t  __zp __r5;
    extern  uint16_t  __zp __r6;
    extern  uint16_t  __zp __r7;
    extern  uint16_t  __zp __r8;
    extern  uint16_t  __zp __r9;
    extern  uint16_t  __zp __r10;
    extern  uint16_t  __zp __r11;
    extern  uint16_t  __zp __r12;
    extern  uint16_t  __zp __r13;
    extern  uint16_t  __zp __r14;
    extern  uint16_t  __zp __r15;
    extern  uint8_t  __zp __r0L;
    extern  uint8_t  __zp __r0H;
    extern  uint8_t  __zp __r1L;
    extern  uint8_t  __zp __r1H;
    extern  uint8_t  __zp __r2L;
    extern  uint8_t  __zp __r2H;
    extern  uint8_t  __zp __r3L;
    extern  uint8_t  __zp __r3H;
    extern  uint8_t  __zp __r4L;
    extern  uint8_t  __zp __r4H;
    extern  uint8_t  __zp __r5L;
    extern  uint8_t  __zp __r5H;
    extern  uint8_t  __zp __r6L;
    extern  uint8_t  __zp __r6H;
    extern  uint8_t  __zp __r7L;
    extern  uint8_t  __zp __r7H;
    extern  uint8_t  __zp __r8L;
    extern  uint8_t  __zp __r8H;
    extern  uint8_t  __zp __r9L;
    extern  uint8_t  __zp __r9H;
    extern  uint8_t  __zp __r10L;
    extern  uint8_t  __zp __r10H;
    extern  uint8_t  __zp __r11L;
    extern  uint8_t  __zp __r11H;
    extern  uint8_t  __zp __r12L;
    extern  uint8_t  __zp __r12H;
    extern  uint8_t  __zp __r13L;
    extern  uint8_t  __zp __r13H;
    extern  uint8_t  __zp __r14L;
    extern  uint8_t  __zp __r14H;
    extern  uint8_t  __zp __r15L;
    extern  uint8_t  __zp __r15H;

## Graphic strings

Graphic strings can be defined by setting up a byte array and using the defined macros as shown here:

    uint8_t ClearScreen[] = {
    	NEWPATTERN, 2,
    	MOVEPENTO, WORD(0), 0,
    	RECTANGLETO, WORD(319), 199,
    	0
    };

Then hand over the address of the graphic string to the GEOS call like this:

    GraphicsString(ClearScreen);

Some of the entries in the graphics string need to be 16-bit values. For that please use the WORD macro which will convert 16 bit constants into lo/hi 8-bit values.

## Menus

To use menus in GEOS you need to set up a menu table and supply that to the `DoMenu` call. For ease of creation of that table some types were created. Please create that menu table like this:

    menu_tab_t EditSubMenu = {
	    .top=SM_TOP, .bot=SM_TOP+1+EM_COUNT*14,
	    .left=EM_LEFT, .right=EM_LEFT+EM_WIDTH,
	    .menu_type_and_count=VERTICAL|EM_COUNT,
	    .items = {
			{ .text="cut", .action_type=MENU_ACTION, .handler_function=R_DoCut },
	        { .text="copy", .action_type=MENU_ACTION, .handler_function=R_DoCopy },
	        { .text="paste", .action_type=MENU_ACTION, .handler_function=R_DoPaste }
        }
    };
    
    menu_tab_t MenuTable = {
        .top=MM_TOP, .bot=MM_BOTTOM, .left=MM_LEFT, .right=MM_RIGHT,
        .menu_type_and_count=MM_COUNT|HORIZONTAL,
        .items = {
	        { .text="geos", .action_type=VERTICAL, .sub_menu  =  &GeosSubMenu },
	        { .text="file", .action_type=VERTICAL, .sub_menu  =  &FileSubMenu },
	        { .text="edit", .action_type=VERTICAL, .sub_menu  =  &EditSubMenu }
        }
    };

Hand over the address of the menu table in the `DoMenu` call:

    DoMenu(&MenuTable, 0);

## Icons

For icons in GEOS you need to set up an icon table and hand that over to the `DoIcons` call. Define it like this:

    icon_table_t  IconTable  = {
	    .num_icons=1, .mouse_x=0, .mouse_y=0,
	    .icons = {
		    { .graphic_data=Icon1Picture, 
		      .left=3, .top=60, .width=ICON1_WIDTH, .height=ICON1_HEIGHT,
		      .service_routine=R_DoIcon1
		    }
	    }
    };

Hand over the address of the icon table in the `DoIcons` call:

    DoIcons(&IconTable);

## Dialog boxes

To easily define dialog boxes a set of macros was defined. Here is an example:

    DB_NAME_SECT(dlgClose, vlir01)
    DB_DEFPOS(1)
    DB_ICON(OK, DBI_X_0, DBI_Y_2)
    DB_TXTSTR(DBI_X_0, DBI_Y_0, close_msg)
    DB_END(dlgClose)

To open the dialog box you need to supply the address of the DB definition table in the `DoDlgBox` call like this:

    DoDlgBox(dlgClose);

This are the predefined macros. Their naming follows GEOS standards. For details please check GEOS programmer documentation:

|Macro                  |Description                                     |
|-----------------------|------------------------------------------------|
| `DB_NAME(name)`       | Starts a DB definition for the resident module |
| `DB_NAME_SECT(name, sect)` | Starts a DB definition for an overlay module.  You need to give the VLIR chain as sect like vlir01 for first overlay. |
| `DB_END(name`)        | Ends a DB definition. For each DB_NAME a matching DB_END must be given. |
| `DB_DEFPOS(pattern)`  | Defines the fill pattern of the shadow. |
| `DB_SETPOS(pattern, top, bottom, left, right)` | Sets the fill pattern and position / size of the DB. |
| `DB_ICON(icon, x, y)` | Defines an icon in the DB. |
| `DB_TXTSTR(x, y, text)` | Defines a constant text. |
| `DB_VARSTR(x, y, zp_ptr)` | Defines a variable text with position and a zero page address to point to the string. |
| `DB_GETSTR(x, y, zp_ptr, length)` | Defines an entry field at a position with maximum length. The zp_ptr is a zero page address which points to a buffer to receice the input string. |
| `DB_SYSOPV()`         | Calls the sysopv vector |
| `DB_GRPHSTR(ptr)`     | Will execute the graphics string addressed by ptr |
| `DB_GETFILES(x, y)`   | Allows file selection at given position |
| `DB_OPVEC(ptr)`       | Calls the vector function addressed by ptr |
| `DB_USRICON(x, y, icon_ptr)` | Shows a user defined icon at given postion. The address of the icon table is given in icon_ptr |
| `DB_USRROUT(ptr)`     | Calls the function pointer to by ptr |


## VLIR overlays

All code and static initialized data go by default in the resident portion (which is stored in VLIR chain 0 of the application).

If you want overlays you have to tag elements with a compiler attribute. The most easy way to do this is to set it on file level:

    #pragma  clang section text=".vlir01.text" data=".vlir01.data" bss=".vlir01.bss"

Using this `#pragma` all functions and variables are stored in the VLIR chain 01. The only exception are string constants. There is a string pooling in place. By default all strings are stored in the resident part (VLIR chain 0). To come around this, please declare initialized static variables to hold the string value:

    /* Define string constants as static variables. This way they will be stored
     * in the vlir record 2 and not in the main constant string pool.
     */
    char cut_msg[] = "cut handler called.";
    char copy_msg[] = "copy handler called.";
    char paste_msg[] = "paste handler called.";
    char icon1_msg[] = "icon handler called.";

This way the string constant will be stored in the VLIR chain set by the `#pragma clang section` command.

## Swapping in code for an overlay

While the linker will store the artifacts for an overlay in a VLIR chain, it is on you to load that code and static data in when needed. First you need to stored the track/sector pointers for each VLIR chain in a swap table at the startup of the application. Please note that the GEOS file type given in the FindFTypes call must match the GEOS file type  of your application:

	/* holds (T,S) pairs, one for each module of our application */
	tr_se_pair_t  swapTable[NUM_MODS];    		
	
	/* holds currently swapped in module number */
	uint8_t  curModule;
	
	/*********************************************************************
    * This routine sets up a table which contains the track and sector
    * numbers for each of the program modules which can be loaded.
    * This table will be used by the SwapMod function later on.
    *********************************************************************/
    void InitSwap(void)
    {
    	char appName[1][17];
    	
    	FindFTypes(appName, APPLICATION, 1, "Sample VLIR V1.0");
    	OpenRecordFile(appName[0]);
    	MoveData((const uint8_t*)&fileHeader+4, (uint8_t*)swapTable, NUM_MODS*2);
    	CloseRecordFile();
    	curModule = 0xff;
    }

Whenever you now need a function or static data of the overlay, you need to load in that VLIR chain BEFORE you use that artifacts:

    /*********************************************************************
    * This routine swaps a module in. Note how it used "ReadFile" instead
    * of "ReadRecord" so that it does not affect any opened VLIR file.
    *********************************************************************/
    noinline void SwapMod(uint8_t req_mod_no)
    {
	    if (req_mod_no != curModule) {
		    curModule = req_mod_no;
		    ReadFile(OVERLAYADDR, OVERLAYSIZE, swapTable[req_mod_no-1]);
	    }
    }

`OVERLAYADDR` and `OVERLAYSIZE` are defined by the linker and default to `0x5000` and `0x1000` (for details see the `vlir.ld` linker script in `.../mos-platform/geos-cbm/vlir.ld`).
You can change the size of the overlay memory to e.g. 8k bytes by adding the following statement to any of your C files:

    SET_OVERLAYSIZE(0x2000)    

## Importing image data

For e.g. icons in GEOS you need image data in a compressed format supported by GEOS. You need to supply it as an byte array like this:

    uint8_t Icon1Picture[] = {
	    /*
	    ** This data was generated by sp65 2.17 - Debian 2.17-1 from
	    ** icon.pcx (48x16, 2 colors, indexed)
	    */
		0x13,0x00,0x81,0x08,0x05,0x00,0x81,0x08,0x05,0x00,0x8F,0x08,0x30,0x62,0xC0,0x00, 
		0x00,0x08,0x81,0x12,0x20,0x00,0x00,0x08,0x81,0x02,0x03,0x00,0x83,0x08,0x81,0x02,    
		0x03,0x00,0x83,0x08,0x81,0x02,0x03,0x00,0x83,0x08,0x81,0x12,0x03,0x00,0x83,0x08,
	    0x30,0x62,0x1A,0x00,
    };
    #define  ICON1_WIDTH (48/8)
    #define  ICON1_HEIGHT  16

### Using GEOS Photo Scraps

One way would be to create that image with geoPaint and export it from there to a  PhotoScrap (by using edit/copy), copy that Photo Scrap File to your host and from there it is quite easy to convert it to an initialized C byte array. 

A photo scrap is a sequential file on disk with a name of “Photo Scrap” and a type of “Photo Scrap V1.1”. It is generally a rectangular monochrome image.

The first three bytes of the file are the dimensions of the image. The width is one byte and is measured in units of 8 pixels. The next two bytes are the height in pixels. The theoretical maximum dimensions of a photo scrap are therefore 2040 (255*8) * 65535, with the width divisible by 8.

The bitmap data uses 8 horizontal pixels per byte (the leftmost pixel is bit 7, 1-bits are black). Consecutive bytes describe a pixel line from left to right. These lines are stored row by row starting from the top.

This bitmap data is stored compressed using a format based on runlength-encoding (RLE). GEOS KERNAL’s “BitmapUp” can decode this format, so applications can just pass the data to the KERNAL’s APIs without having to care about the specific encoding.

### Using the sp65 tool from cc65 compiler

Another way of doing it is to create the image as a pcx file and convert that file with sp65 tool. sp65 is part of the cc65 compiler and is also documented there.

# Debugging your application

Right now there is no debugger on source code level. But there are some tools which can make debugging a GEOS program written in C much easier.

## Listing assembler code and symbols

Sometimes you need to understand which code finally was created by the compiler. You can do this easily with the llvm-objdump command on the generated .elf file.
With the command

    llvm-objdump -d --line-numbers --source --show-all-symbols -T --syms myapp.cvt.elf

you can examine the generated assembler code, the value of symbols and in which VLIR chain a symbol had been placed by the compiler. The llvm-objdump has many more options to explore.

## Generating a symbol map file for VICE monitor

Debugging with the vice monitor is one of the most convenient ways to check and debug you GEOS application. The monitor allows to load a label file made of symbol names and their addresses. This allows the monitor to show the symbols in disassembly and data instead of raw addresses.

To generate the vice label file you can use a utility of llvm-mos. Please use this command:

    .../llvm-mos-sdk/utils/vicelbl myapp.cvt.elf > myapp.lbl

You can apply that lbl file either at the command line when starting `x64` by adding the option `-moncommands myapp.lbl` or inside vice in the monitor with the `load_label` command.

If you have not installed the source code of the llvm-mos-sdk you can create that lbl file by the following command line:

    nm myapp.cvt.elf | awk '{ print "add_label", substr($1, 5), gensub(/^[^.]/, ".\\0", 1, $3); }'
