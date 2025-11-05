#ifndef _BIOS_H_
#define _BIOS_H_

#ifdef __cplusplus
extern "C" {
#endif

struct fds_bios_disk_id {
  unsigned char licensee;
  char name[4];
  char version;
  char side_num;
  char disk_num;
  char disk_type;
  char _unk;
  char num_files;
};

struct fds_bios_file_header {
  char id;
  char name[8];
  char *dest;
  unsigned int size;
  char type;
  char *source;
  char source_type;
};

#define FDS_XFR_MODE_COPY 0
#define FDS_XFR_MODE_FILL 1

#define FDS_XFR_INC_1 0
#define FDS_XFR_INC_32 1

struct fds_bios_vram_transfer {
  unsigned int address;
  unsigned int length : 6;
  unsigned int mode : 1;
  unsigned int increment : 1;
};

#define FDS_OBJ_NORMAL 0x00
#define FDS_OBJ_SKIP 0x01
#define FDS_OBJ_HIDE 0x80

struct fds_bios_object {
  unsigned char render_flag;
  unsigned char y;
  unsigned char y_fractional;
  unsigned char x;
  unsigned char x_fractional;
  unsigned char anim_frame;
  unsigned int tile_arrange_ptr;
  struct {
    unsigned int flip_y : 1;
    unsigned int _unused : 3;
    unsigned int flip_x : 1;
  } flags;
  unsigned char palette;
  struct {
    unsigned int width : 4;
    unsigned int height : 4;
  } size;
  unsigned char oam_idx;
};

struct fds_bios_pads {
  unsigned char pad[2];
  unsigned char exp[2];
};

struct fds_bios_pads_combined {
  unsigned char pad_1;
  unsigned char pad_2;
};

struct fds_bios_trans_pads {
  unsigned char trans[2];
  unsigned char data[2];
};

struct fds_bios_trans_exp_pads {
  unsigned char trans[4];
  unsigned char data[4];
};

struct fds_bios_coords {
  unsigned char y;
  unsigned char x;
};

struct fds_bios_keyboard_data {
  char clr_home : 1;
  char up : 1;
  char right : 1;
  char left : 1;
  char down : 1;
  char space : 1;
  char del : 1;
  char ins : 1;

  char f1 : 1;
  char esc : 1;
  char q : 1;
  char ctr : 1;
  char lshift : 1;
  char grph : 1;
  char one : 1;
  char two : 1;

  char f2 : 1;
  char w : 1;
  char s : 1;
  char a : 1;
  char x : 1;
  char z : 1;
  char e : 1;
  char three : 1;

  char f3 : 1;
  char t : 1;
  char r : 1;
  char d : 1;
  char f : 1;
  char c : 1;
  char five : 1;
  char four : 1;

  char f4 : 1;
  char y : 1;
  char g : 1;
  char h : 1;
  char b : 1;
  char v : 1;
  char seven : 1;
  char six : 1;

  char f5 : 1;
  char i : 1;
  char u : 1;
  char j : 1;
  char m : 1;
  char n : 1;
  char nine : 1;
  char eight : 1;

  char f6 : 1;
  char o : 1;
  char l : 1;
  char k : 1;
  char period : 1;
  char comma : 1;
  char p : 1;
  char zero : 1;

  char f7 : 1;
  char at : 1;
  char colon : 1;
  char semicolon : 1;
  char underscore : 1;
  char slash : 1;
  char dash : 1;
  char caret : 1;

  char f8 : 1;
  char ret : 1;
  char lbracket : 1;
  char rbracket : 1;
  char kana : 1;
  char rshift : 1;
  char yen : 1;
  char stop : 1;
};

// Load files from disk.
__attribute__((leaf)) char fds_bios_LoadFiles(struct fds_bios_disk_id *disk_id,
                                              char *file_ids, char *loaded);
// Append a file to disk.
__attribute__((leaf)) char
fds_bios_AppendFile(struct fds_bios_disk_id *disk_id,
                    struct fds_bios_file_header *file_header);
// Write a file to disk.
__attribute__((leaf)) char
fds_bios_WriteFile(struct fds_bios_disk_id *disk_id,
                   struct fds_bios_file_header *file_header, char file_num);
// Compare and set the file count on disk.
__attribute__((leaf)) char
fds_bios_CheckFileCount(struct fds_bios_disk_id *disk_id, char count);
// Decrement the file count on disk.
__attribute__((leaf)) char
fds_bios_AdjustFileCount(struct fds_bios_disk_id *disk_id, char count);
// Set the file count + 1.
__attribute__((leaf)) char
fds_bios_SetFileCount1(struct fds_bios_disk_id *disk_id, char count);
// Set the file count.
__attribute__((leaf)) char
fds_bios_SetFileCount(struct fds_bios_disk_id *disk_id, char count);
// Get the ID info of the current disk.
__attribute__((leaf)) char
fds_bios_GetDiskInfo(struct fds_bios_disk_id *disk_id);

// Compares the current disk header to the input string.
char fds_bios_CheckDiskHeader(char string[10]);
// Gets the listed amount of files from disk.
unsigned char fds_bios_GetNumFiles(void);
// Set the listed amount of files on disk.
void fds_bios_SetNumFiles(unsigned char num);
// Loads the provided file IDs from disk. Returns 0x00 if a match is found, or
// 0xFF if no match is found (or an entry in the list with a value of 0xFF is
// found).
char fds_bios_FileMatchTest(char *ids);
// Skip loading the given amount of files.
void fds_bios_SkipFiles(unsigned char num);

// Delay by (at least) 131 CPU cycles.
void fds_bios_Delay131(void);
// Delay by (approximately) the given value in milliseconds.
__attribute__((leaf)) void fds_bios_Delayms(char delay);

// Disable sprite/background rendering.
void fds_bios_DisPFObj(void);
// Enable sprite/background rendering.
void fds_bios_EnPFObj(void);
// Disable sprite rendering.
void fds_bios_DisObj(void);
// Enable sprite rendering.
void fds_bios_EnObj(void);
// Disable background rendering.
void fds_bios_DisPF(void);
// Enable background rendering.
void fds_bios_EnPF(void);

// Wait until next vblank NMI.
void fds_bios_VINTWait(void);

// Convert pixel coordinates to a nametable address.
unsigned fds_bios_Pixel2NamConv(struct fds_bios_coords coords);
// Convert a nametable address to pixel coordinates.
struct fds_bios_coords fds_bios_Nam2PixelConv(unsigned addr);

// Perform sprite DMA. Should be used after `fds_bios_UploadObject`.
void fds_bios_SpriteDMA(void);

// Read hardwired and expansion joypads.
struct fds_bios_pads fds_bios_ReadPads(void);
// Combines inputs from hardwired and expansion joypads.
// Use after `fds_bios_ReadPads`.
struct fds_bios_pads_combined fds_bios_OrPads(struct fds_bios_pads pads);
// Read up/down button transitions on hardwired joypads.
struct fds_bios_trans_pads *fds_bios_ReadDownPads(void);
// Read up/down button transitions on hardwired and expansion joypads.
struct fds_bios_trans_pads *fds_bios_ReadOrDownPads(void);
// Read up/down button transitions on hardwired joypads until two reads match.
struct fds_bios_trans_pads *fds_bios_ReadDownVerifyPads(void);
// Read up/down button transitions on hardwired and expansion joypads until two
// reads match.
struct fds_bios_trans_pads *fds_bios_ReadOrDownVerifyPads(void);
// Read up/down button transitions on hardwired and expansion joypads
// separately.
struct fds_bios_trans_exp_pads *fds_bios_ReadDownExpPads(void);

// If tile_row > 0x20, fills pattern table with value for 16 * rows_attr tiles.
// If tile_row > = 0x20, fills corresponding nametable with value and attribute
// table with rows_attr.
__attribute__((leaf)) void fds_bios_VRAMFill(char tile_row, char value,
                                             char rows_attr);
// Fill a section of RAM with a value.
__attribute__((leaf)) void fds_bios_MemFill(char value, char start, char end);

// Reads from the Family BASIC Keyboard. Returns 0x00 if not connected, 0xFF if
// no errors.
__attribute__((leaf)) char
fds_bios_ReadKeyboard(struct fds_bios_keyboard_data *data);

// Uploads an object to be used with `fds_bios_SpriteDMA`.
void fds_bios_UploadObject(struct fds_bios_object *obj);

#ifdef __cplusplus
}
#endif

#endif
