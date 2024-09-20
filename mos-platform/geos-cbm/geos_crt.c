/***********************************************************************
 * geos_crt.c
 *
 * This file contains the implemantation of the "C" definition of
 * all geos OS calls for use in GEOS applications  with llvm-mos
 * C compiler.
 *
 * Transcribed from geoProgrammer manual by DiSc.
 *
 ***********************************************************************/

#include "geos.h"

/***********************************************************************
 * GEOS Graphic routines
 ***********************************************************************/

void DrawPoint(uint16_t x, uint8_t y, bool recover, bool background)
{
  __r3 = x;
  __r11L = y;
  if (recover) {
    __attribute__((leaf))
    asm volatile("lda #0xff \n");
  } else {
    if (background) {
      __attribute__((leaf))
      asm volatile("clc \n");
    } else {
      __attribute__((leaf))
      asm volatile("sec \n");
    }
    __attribute__((leaf))
    asm volatile("lda #0 \n");
  }
  __attribute__((leaf))
  asm volatile("jsr __DrawPoint " : : : "a","x","y","c","v");
}

bool TestPoint(uint16_t x, uint8_t y)
{
  bool is_pixel_set;

  __r3 = x;
  __r11L = y;
  __attribute__((leaf))
  asm volatile("jsr __TestPoint \n"
               "ldx #0 \n"
               "bcc pixel_unset \n"
               "inx \n"
               "pixel_unset:" : "=x" (is_pixel_set) : : "a","y","c","v");
  return is_pixel_set;
}

void HorizontalLine(uint16_t left, uint16_t right, uint8_t y, uint8_t pattern)
{
  __r11L = y;
  __r3 = left;
  __r4 = right;
  __attribute__((leaf))
  asm volatile("jsr __HorizontalLine " : "=a" (pattern) : "a" (pattern) : "x","y","c","v");
}

void VerticalLine(uint16_t x, uint8_t top, uint8_t bottom, uint8_t pattern)
{
  __r3L = top;
  __r3H = bottom;
  __r4 = x;
  __attribute__((leaf))
  asm volatile("jsr __VerticalLine " : "=a" (pattern) : "a" (pattern) : "x","y","c","v");
}

void InvertLine(uint16_t left, uint16_t right, uint8_t y)
{
  __r3 = left;
  __r4 = right;
  __r11L = y;
  __attribute__((leaf))
  asm volatile("jsr __InvertLine " : : : "a","x","y","c","v");
}

void RecoverLine(uint16_t left, uint16_t right, uint8_t y)
{
  __r3 = left;
  __r4 = right;
  __r11L = y;
  __attribute__((leaf))
  asm volatile("jsr __RecoverLine " : : : "a","x","y","c","v");
}

void DrawLine(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom, bool recover, bool background)
{
  __r3 = left;
  __r11L = top;
  __r4 = right;
  __r11H = bottom;

  if (recover) {
    __attribute__((leaf))
    asm volatile("lda #0xff \n");
  } else {
    if (background) {
      __attribute__((leaf))
      asm volatile("clc \n");
    } else {
      __attribute__((leaf))
      asm volatile("sec \n");
    }
    __attribute__((leaf))
    asm volatile("lda #0 \n");
  }

  __attribute__((leaf)) 
  asm volatile("jsr __DrawLine " : : : "a","x","y","c","v");
}

void SetPattern(uint8_t pattern)
{
  __attribute__((leaf))
  asm volatile("jsr __SetPattern " : "=a"(pattern) : "a"(pattern) : "c","v");
}

void Rectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom)
{
  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;
  __attribute__((leaf))
  asm volatile("jsr __Rectangle " : : : "a","x","y","c","v");
}

void FrameRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom, uint8_t pattern)
{
  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;
  __attribute__((leaf))
  asm volatile("jsr __FrameRectangle" : "=a"(pattern) : "a"(pattern) : "x","y","c","v");
}

void InvertRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom)
{
  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;
  __attribute__((leaf))
  asm volatile("jsr __InvertRectangle " : : : "a","x","y","c","v");
}

void RecoverRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom)
{
  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;
  __attribute__((leaf))
  asm volatile("jsr __RecoverRectangle " : : : "a","x","y","c","v");
}

void ImprintRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom)
{
  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;__attribute__((leaf))
  asm volatile("jsr __ImprintRectangle " : : : "a","x","y","c","v");
}

void BitmapUp(const uint8_t *bitmap, uint8_t card_left, uint8_t top, uint8_t card_width, uint8_t height)
{
  __r0 = (uint16_t)bitmap;
  __r1L = card_left;
  __r1H = top;
  __r2L = card_width;
  __r2H = height;
  __attribute__((leaf))
  asm volatile("jsr __BitmapUp " : : : "a","x","y","c","v");
}

void BitmapClip(const uint8_t *bitmap, uint8_t card_left, uint8_t top, uint8_t card_width, uint8_t height,
                uint8_t left_skip, uint8_t right_skip, uint16_t top_skip)
{
  __r0 = (uint16_t)bitmap;
  __r1L = card_left;
  __r1H = top;
  __r2L = card_width;
  __r2H = height;

  __r11L = left_skip;
  __r11H = right_skip;
  __r12 = top_skip;

  __attribute__((leaf))
  asm volatile("jsr __BitmapClip " : : : "a","x","y","c","v");
}

void BitOtherClip(const uint8_t *bitmap, uint8_t card_left, uint8_t top, uint8_t card_width, uint8_t height,
                  uint8_t left_skip, uint8_t right_skip, uint16_t top_skip,
                  vector app_input, vector sync)
{
  __r0 = (uint16_t)bitmap;
  __r1L = card_left;
  __r1H = top;
  __r2L = card_width;
  __r2H = height;

  __r11L = left_skip;
  __r11H = right_skip;
  __r12 = top_skip;
  __r13 = (uint16_t)app_input;
  __r14 = (uint16_t)sync;

  __attribute__((leaf))
  asm volatile("jsr __BitOtherClip " : : : "a","x","y","c","v");
}

void GraphicsString(const uint8_t *graph_string)
{
  __r0 = (uint16_t)graph_string;
  __attribute__((leaf))
  asm volatile("jsr __GraphicsString " : : : "a","x","y","c","v");
}

void GetScanLine(uint8_t y, uint16_t *first_screen_byte, uint16_t *first_backgr_byte)
{
  __attribute__((leaf))
  asm volatile("jsr __GetScanLine" : : "x"(y) : "a","c","v");
  *first_screen_byte = __r5;
  *first_backgr_byte = __r6;
}

/***********************************************************************
 * GEOS Character routines
 ***********************************************************************/

void PutString(uint16_t x, uint8_t y, const char *str)
{
  __r11 = x;
  __r1H = y;
  __r0 = (uint16_t)str;
  __attribute__((leaf))
  asm volatile("jsr __PutString " : : : "a","x","y","c","v");
}

void PutDecimal(uint16_t value, uint16_t x, uint8_t y, uint8_t format)
{
  __r0 = value;
  __r11 = x;
  __r1H = y;
  __attribute__((leaf))
  asm volatile("jsr __PutDecimal" : "=a"(format) : "a"(format) : "x","y","c","v");
}

uint8_t GetString(char *buffer, uint16_t x, uint8_t y, uint8_t max_chars, vector fault)
{
  uint8_t len;

  __r0 = (uint16_t)buffer;
  __r11 = x;
  __r1H = y;
  __r2L = max_chars;

  __r4 = (uint16_t)fault;
  if (fault != 0) 
    __r1L = 0x80;
  else
    __r1L = 0;
  __attribute__((leaf))
  asm volatile("jsr __GetString " : "=x" (len) : : "a","y","c","v");

  return len;
}

char GetNextChar(void)
{
  char ch;

  __attribute__((leaf))
  asm volatile("jsr __GetNextChar " : "=a"(ch) : : "x","c","v");
  return ch;
}

void InitTextPrompt(uint8_t height)
{
  __attribute__((leaf))
  asm volatile("jsr __InitTextPrompt " : "=a"(height) : "a"(height) : "x","y","c","v");
}

void PromptOn(void)
{
  __attribute__((leaf))
  asm volatile(" jsr __PromptOn" : : : "a","x","c","v");
}

void PromptOff(void)
{
  __attribute__((leaf))
  asm volatile(" jsr __PromptOff" : : : "a","x","c","v");
}

uint16_t PutChar(uint16_t x, uint8_t y, char ch)
{
  __r11 = x;
  __r1H = y;

  __attribute__((leaf))
  asm volatile("jsr __PutChar " : "=a" (ch) : "a" (ch) : "x","y","c","v");

  return __r11;
}

uint16_t SmallPutchar(uint16_t x, uint8_t y, char ch)
{
  __r1H = y;
  __r11 = x;
  __attribute__((leaf))
  asm volatile("jsr __SmallPutchar" : "=a"(ch) : "a"(ch) : "x", "y", "c", "v");

  return __r11;
}

void GetRealSize(char ch, uint8_t mode, uint8_t *width, uint8_t *height, uint8_t *baseline_offset)
{
  uint8_t w, h, o;

  __attribute__((leaf))
  asm volatile("jsr __GetRealSize" : "=a"(o), "=y"(w), "=x"(h) : "a"(ch), "x"(mode) : "c","v");
  *width = w;
  *height = h;
  *baseline_offset = o;
}

uint8_t GetCharWidth(char ch)
{
  uint8_t width;

  __attribute__((leaf))
  asm volatile("jsr __GetCharWidth" : "=a"(width) : "a"(ch) : "y","c","v");
  return width;
}

void LoadCharSet(uint8_t *font_info_tab)
{
  __r0 = (uint16_t)font_info_tab;
  __attribute__((leaf))
  asm volatile("jsr __LoadCharSet" : : : "a","y","c","v");
}

void UseSystemFont(void)
{
  __attribute__((leaf))
  asm volatile("jsr __UseSystemFont" : : : "a","x","y","c","v");
}

/***********************************************************************
 * GEOS Mouse routines
 ***********************************************************************/

void InitMouse(void)
{
  __attribute__((leaf))
  asm volatile("jsr __InitMouse " : : : "a","x","y","c","v");
}

void InitMouse_128(void)
{
  __attribute__((leaf))
  asm volatile("jsr __InitMouse_128 " : : : "a","x","y","c","v");
}

void SlowMouse(void)
{
  __attribute__((leaf))
  asm volatile("jsr __SlowMouse " : : : "a","x","y","c","v");
}

void SlowMouse_128(void)
{
  __attribute__((leaf))
  asm volatile("jsr __SlowMouse_128 " : : : "a","x","y","c","v");
}

void UpdateMouse(void)
{
  __attribute__((leaf))
  asm volatile("jsr __UpdateMouse " : : : "a","x","y","c","v");
}

void UpdateMouse128(void)
{
  __attribute__((leaf))
  asm volatile("jsr __UpdateMouse_128 " : : : "a","x","y","c","v");
}

void SetMouse(void)
{
  __attribute__((leaf))
  asm volatile("jsr __SetMouse " : : : "a","x","y","c","v");
}

void SetMouse_128(void)
{
  __attribute__((leaf))
  asm volatile("jsr __SetMouse_128" : : : "a", "x", "y", "c", "v");
}

void StartMouseMode(uint16_t x, uint8_t y)
{
  __r11 = x;
  __attribute__((leaf))
  asm volatile(
    "sec \n"
    "jsr __StartMouseMode " : "=y"(y) : "y"(y) : "a","x","c","v"
  );
}

void ClearMouseMode(void)
{
  __attribute__((leaf))
  asm volatile("jsr __ClearMouseMode " : : : "a","x","y","c","v");
}

void MouseOff(void)
{
  __attribute__((leaf))
  asm volatile("jsr __MouseOff " : : : "a","c","v");
}

void MouseUp(void)
{
  __attribute__((leaf))
  asm volatile("jsr __MouseUp " : : : "a","c","v");
}

bool IsMseInRegion(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom)
{
  bool is_in;

  __r3 = left;
  __r2L = top;
  __r4 = right;
  __r2H = bottom;
  __attribute__((leaf))
  asm volatile("jsr __IsMseInRegion " : "=a"(is_in) : : "c","v");
  
  return is_in;
}

/***********************************************************************
 * GEOS Sprite support
 ***********************************************************************/

void DrawSprite(uint8_t sprite_no, const uint8_t *sprite_data)
{
  __r3L = sprite_no;
  __r4 = (uint16_t)sprite_data;
  __attribute__((leaf))
  asm volatile("jsr __DrawSprite " : : : "a","y","c","v");
}

void PosSprite(uint8_t sprite_no, uint16_t x, uint8_t y)
{
  __r3L = sprite_no;
  __r4 = x;
  __r5L = y;
  __attribute__((leaf))
  asm volatile("jsr __PosSprite" : : : "a","x","y","c","v");
}

void EnablSprite(uint8_t sprite_no)
{
  __r3L = sprite_no;
  __attribute__((leaf))
  asm volatile("jsr __EnablSprite" : : : "a","x","c","v");
}

void DisablSprite(uint8_t sprite_no)
{
  __r3L = sprite_no;
  __attribute__((leaf))
  asm volatile("jsr __DisablSprite" : : : "a","x","c","v");
}

/***********************************************************************
 * GEOS Process Support
 ***********************************************************************/

void InitProcesses(uint8_t num_of_processes, const uint8_t *process_table)
{
  __r0 = (uint16_t)process_table;
  __attribute__((leaf))
  asm volatile("jsr __InitProcesses" : "=a" (num_of_processes) : "a" (num_of_processes) : "x","y","c","v");
}

void RestartProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __RestartProcess" : : "x" (process_num) : "a","c","v");
}

void BlockProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __BlockProcess" : : "x" (process_num) : "a","c","v");
}

void UnblockProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __UnblockProcess" : : "x" (process_num) : "a","c","v");
}

void FreezeProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __FreezeProcess" : : "x" (process_num) : "a","c","v");
}

void UnfreezeProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __UnfreezeProcess" : : "x" (process_num) : "a","c","v");
}

void Sleep(uint16_t jiffies)
{
  __r0 = jiffies;
  __attribute__((leaf))
  asm volatile("jsr __Sleep" : : : "a","x","y","c","v");
}

void EnableProcess(uint8_t process_num)
{
  __attribute__((leaf))
  asm volatile("jsr __EnableProcess" : : "x" (process_num) : "a","c","v");
}

/***********************************************************************
 * GEOS Menu, Dialog Boxes & Icons routines
 ***********************************************************************/

uint8_t DoDlgBox(uint8_t *dlg_table)
{
  __r0 = (uint16_t)dlg_table;
  __attribute__((leaf))
  asm volatile("jsr __DoDlgBox " : : : "a","x","y","c","v");
  return __r0L;
}

void RstrFrmDialog(uint8_t icon_no)
{
  sysDBData = icon_no;
  __attribute__((leaf))
  asm volatile("jsr __RstrFrmDialog " : : : "a","x","y","c","v");
}

void DoMenu(const menu_tab_t* menu_table, uint8_t selected_menu_no)
{
  __r0 = (uint16_t)menu_table;
  __attribute__((leaf))
  asm volatile("jsr __DoMenu " : "=a" (selected_menu_no) : "a" (selected_menu_no) : "x","y","c","v");
}

void DoPreviousMenu(void)
{
  __attribute__((leaf))
  asm volatile("jsr __DoPreviousMenu " : : : "a","x","y","c","v");
}

void ReDoMenu(void)
{
  __attribute__((leaf))
  asm volatile("jsr __ReDoMenu " : : : "a","x","y","c","v");
}

void RecoverMenu(void)
{
  __attribute__((leaf))
  asm volatile("jsr __RecoverMenu " : : : "a","x","y","c","v");
}

void RecoverAllMenus(void)
{
  __attribute__((leaf))
  asm volatile("jsr __RecoverAllMenus" : : : "a","x","y","c","v");
}

void GotoFirstMenu(void)
{
  __attribute__((leaf))
  asm volatile("jsr __GotoFirstMenu" : : : "a","x","y","c","v");
}

void DoIcons(const icon_table_t* icon_table)
{
  __r0 = (uint16_t)icon_table;

  __attribute__((leaf))
  asm volatile("jsr __DoIcons " : : : "a","x","y","c","v");
}

/***********************************************************************
 * MISC & General Utitlities
 ***********************************************************************/

uint16_t GetRandom(void)
{
  __attribute__((leaf))
  asm volatile("jsr __GetRandom " : : : "a","c","v");
  return random;
}

void CopyString(char *src, char *dest)
{
  __r0 = (uint16_t)src;
  __r1 = (uint16_t)dest;
  __attribute__((leaf))
  asm volatile(
      "ldx   #2 \n"
      "ldy   #4 \n"
      "jsr   __CopyString " : : : "a","x","y","c","v");
}

void CopyFString(uint8_t *src, uint8_t *dest, uint8_t count)
{
  __r0 = (uint16_t)src;
  __r1 = (uint16_t)dest;
  __attribute__((leaf))
  asm volatile(
      "ldx   #2 \n"
      "ldy   #4 \n"
      "jsr   __CopyFString " : "=a" (count) : "a" (count) : "x","y","c","v");
}

int8_t CmpString(char *src, char *dest)
{
  uint8_t result;

  __r0 = (uint16_t)src;
  __r1 = (uint16_t)dest;
  __attribute__((leaf)) asm volatile(
    "           ldx   #2 \n"
    "           ldy   #4 \n"
    "           jsr   __CmpString \n"
    "           beq   __cmp_eq \n"
    "           bmi   __cmp_lt \n"
    "           lda   #1 \n"
    "           bpl   __cmp_done \n"
    "__cmp_lt:  lda   #0xff \n"
    "           bmi   __cmp_done \n"
    "__cmp_eq:  lda   #0 \n"
    "__cmp_done: " : "=a" (result) : : "x","y","c","v");
    
    return result;
}

int8_t CmpFString(char *src, char *dest, uint8_t count)
{
  uint8_t result;

  __r0 = (uint16_t)src;
  __r1 = (uint16_t)dest;
  __attribute__((leaf)) asm volatile(
    "           ldx   #2 \n"
    "           ldy   #4 \n"
    "           jsr   __CmpFString \n"
    "           beq   __cmp_eq \n"
    "           bmi   __cmp_lt \n"
    "           lda   #1 \n"
    "           bpl   __cmp_done \n"
    "__cmp_lt:  lda   #0xff \n"
    "           bmi   __cmp_done \n"
    "__cmp_eq:  lda   #0 \n"
    "__cmp_done:" : "=a" (result) : "a" (count) : "x","y","c","v");
    
    return result;
}

void Panic(void)
{
  asm volatile("jsr __Panic " : : : "a","x","y","c","v");
}

void MoveData(const void* src, void* dest, uint16_t count)
{
  __r0 = (uint16_t)src;
  __r1 = (uint16_t)dest;
  __r2 = count;
  __attribute__((leaf)) 
  asm volatile("jsr __MoveData " : : : "a","y","c","v");
}

void ClearRam(void* memory, uint16_t count)
{
  __r0 = count;
  __r1 = (uint16_t)memory;
  __attribute__((leaf)) 
  asm volatile ("jsr __ClearRam " : : : "a","y","c","v");
}

void FillRam(void* memory, uint16_t count, uint8_t value)
{
  __r0 = count;
  __r1 = (uint16_t)memory;
  __r2L = value;
  __attribute__((leaf)) 
  asm volatile ("jsr __FillRam " : : : "a","y","c","v");
}

void InitRam(uint8_t* init_table)
{
  __r0 = (uint16_t)init_table;
  __attribute__((leaf)) 
  asm volatile ("jsr __InitRam " : : : "a","x","y","c","v");
}

uint16_t GetSerialNumber(void)
{
  __attribute__((leaf)) 
  asm volatile ("jsr __GetSerialNumber " : : : "a","c","v");
  return __r0;
}

void ToBasic(uint8_t* basic_cmd)
{
  __r7 = (uint16_t)basic_cmd;
  __attribute__((leaf)) 
  asm volatile ("jsr __swap_userzp \n"
                "jsr __ToBasic " : : : "a","x","y","c","v");
}

void FirstInit(void)
{
  __attribute__((leaf)) 
  asm volatile ("jsr __FirstInit " : : : "a","x","y","c","v");
}

uint16_t CRC(uint8_t* data, uint16_t count)
{
  __r0 = (uint16_t)data;
  __r1 = count;
  __attribute__((leaf)) 
  asm volatile ("jsr __CRC" : : : "a","x","y","c","v");
  return __r2;
}

/***********************************************************************
 * GEOS High-Level Disk & File Routines
 ***********************************************************************/

disk_err_t ChangeDiskDevice(uint8_t device)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ChangeDiskDevice \n" 
    "jsr __swap_userzp ": "=x" (errno), "=a" (device) : "a" (device) : "y", "c", "v");
    
  return errno;
}

disk_err_t SetDevice(uint8_t device)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __SetDevice \n" 
    "jsr __swap_userzp ": "=x" (errno), "=a" (device) : "a" (device) : "y", "c", "v");
    
  return errno;
}

disk_err_t OpenDisk(char** disk_name)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __OpenDisk \n" 
    "jsr __swap_userzp ": "=x" (errno) : : "a","y","c","v");
    *disk_name = (char*)__r5;
    
  return errno;
}

void GetPtrCurDkNm(disk_name_t buffer)
{
  __attribute__((leaf)) asm volatile(
    "ldx #2 \n"
    "jsr __swap_userzp \n"
    "jsr __GetPtrCurDkNm \n"
    "jsr __swap_userzp " : : : "a","x","y", "c", "v"
  );
  uint8_t idx = 0;
  const char* p = (const char*)__r0;
  while ((idx < DK_NM_ID_LEN) && (*p != (char)0xa0)) {
    buffer[idx++] = *p++;
  }
  if (idx < DK_NM_ID_LEN)
    buffer[idx] = '\0';
}

disk_err_t SetGEOSDisk(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile (    
    "jsr __swap_userzp \n"
    "jsr __SetGEOSDisk \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

bool ChkDkGEOS(dir_header_t* dir_header)
{
  __r5 = (uint16_t)dir_header;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ChkDkGEOS \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
  return isGEOS;
}

uint8_t FindFTypes(char file_names[][17], geos_file_type_t file_type, uint8_t max_filenames, const char* permanent_name)
{
  __r6 = (uint16_t)file_names;
  __r7L = file_type;
  __r7H = max_filenames;
  __r10 = (uint16_t)permanent_name;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FindFTypes \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );

  return __r7H;
}

disk_err_t GetFile(const char* file_name, uint8_t loadOptFlg, const char* disk_name, const char* data_file, uint8_t* load_addr, uint8_t daRecFlg)
{
  disk_err_t errno;

  __r6 = (uint16_t)file_name;
  __r0L = loadOptFlg;
  __r2 = (uint16_t)disk_name;
  __r3 = (uint16_t)data_file;
  __r7 = (uint16_t)load_addr;
  __r10L = daRecFlg;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t FindFile(const char* file_name, tr_se_pair_t* tr_se, dir_entry_t* dir_entry)
{
  disk_err_t errno;

  __r6 = (uint16_t)file_name;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FindFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y", "c", "v"
  );
  tr_se->track = __r1L;
  tr_se->sector = __r1H;
  dir_entry = (dir_entry_t*)__r5;

  return errno;
}

disk_err_t SaveFile(file_header_block_t* header_block, uint8_t dir_page)
{
  disk_err_t errno;

  __r9 = (uint16_t)header_block;
  __r10L = dir_page;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __SaveFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );
  
  return errno;
}

disk_err_t DeleteFile(const char* file_name)
{
  disk_err_t errno;

  __r0 = (uint16_t)file_name;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __DeleteFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t RenameFile(const char* old_name, const char* new_name)
{
  disk_err_t errno;

  __r6 = (uint16_t)old_name;
  __r0 = (uint16_t)new_name;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __RenameFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

uint16_t CalcBlksFree(dir_header_t* dir_header, uint16_t* total_blocks)
{
  __r5 = (uint16_t)dir_header;

  __attribute__((leaf)) asm volatile("jsr __CalcBlksFree" : : : "a","y","c","v");

  *total_blocks = __r3;
  return __r4;
}

/***********************************************************************
 * GEOS Intermediate-Level File Routines
 ***********************************************************************/

disk_err_t GetBlock(tr_se_pair_t tr_se, disk_block_t* disk_block)
{
  disk_err_t errno;

  __r1L = tr_se.track;
  __r1H = tr_se.sector;
  __r4 = (uint16_t)disk_block;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t PutBlock(tr_se_pair_t tr_se, const disk_block_t* disk_block)
{
  disk_err_t errno;

  __r1L = tr_se.track;
  __r1H = tr_se.sector;
  __r4 = (uint16_t)disk_block;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PutBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t GetFHdrInfo(const dir_entry_t* dir_entry, tr_se_pair_t* tr_se, uint8_t** load_addr)
{
  disk_err_t errno;

  __r9 = (uint16_t)dir_entry;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetFHdrInfo \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  tr_se->track = __r1L;
  tr_se->sector = __r1H;
  *load_addr = (uint8_t*)__r7;

  return errno;
}

disk_err_t ReadFile(uint8_t* buffer, uint16_t bufsize, tr_se_pair_t tr_se)
{
  disk_err_t errno;

  __r7 = (uint16_t)buffer;
  __r1L = tr_se.track;
  __r1H = tr_se.sector;
  __r2 = bufsize;


  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t WriteFile(const uint8_t* buffer, tr_se_pair_t* blocks)
{
  disk_err_t errno;

  __r7 = (uint16_t)buffer;
  __r6 = (uint16_t)blocks;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __WriteFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t ReadByteInit(tr_se_pair_t tr_se, disk_block_t* buffer, uint8_t* value)
{
  disk_err_t errno;
  uint8_t v;

  __r1L = tr_se.track;
  __r1H = tr_se.sector;
  __r4 = (uint16_t)buffer;
  __r5L = 0;
  __r5H = 0;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadByte \n"
    "jsr __swap_userzp " : "=x" (errno), "=a" (v) : : "y","c","v"
  );

  *value = v;
  return errno;
}

disk_err_t ReadByteNext(uint8_t* value)
{
  disk_err_t errno;
  uint8_t v;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadByte \n"
    "jsr __swap_userzp " : "=x" (errno), "=a" (v) : : "y","c","v"
  );

  *value = v;
  return errno;
}

disk_err_t GetDirHead(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetDirHead \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t PutDirHead(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PutDirHead \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t NewDisk(void)
{
  disk_err_t errno;
  __r1L = 18;
  __r1H = 0;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __NewDisk \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t LdApplic(dir_entry_t* dir_entry, uint8_t loadOptFlg, const char* disk_name, const char* data_file, uint8_t* load_addr)
{
  disk_err_t errno;

  __r9 = (uint16_t)dir_entry;
  __r0L = loadOptFlg;
  __r2 = (uint16_t)disk_name;
  __r3 = (uint16_t)data_file;
  __r7 = (uint16_t)load_addr;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __LdApplic \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t LdDeskAcc(dir_entry_t* dir_entry)
{
  disk_err_t errno;

  __r9 = (uint16_t)dir_entry;
  __r10L = 0;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __LdDeskAcc \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t LdFile(dir_entry_t* dir_entry)
{
  disk_err_t errno;

  __r9 = (uint16_t)dir_entry;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __LdFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t StartAppl(uint8_t loadOptFlg, const char* disk_name, const char* data_file, uint8_t* start_addr)
{
  disk_err_t errno;

  __r0L = loadOptFlg;
  __r2 = (uint16_t)disk_name;
  __r3 = (uint16_t)data_file;
  __r7 = (uint16_t)start_addr;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __StartAppl \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

void RstrAppl(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __RstrAppl \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

disk_err_t GetFreeDirBlk(uint8_t dir_page_no, uint8_t* free_entry_idx, uint8_t* page_no)
{
  disk_err_t errno;
  uint8_t idx;

  __r10L = dir_page_no;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetFreeDirBlk \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (idx) : : "a","c", "v"
  );

  *free_entry_idx = idx;
  *page_no = __r10L;

  return errno;
}

disk_err_t BlkAlloc(uint16_t bytecount, const tr_se_pair_t* tr_se_tab, uint16_t* blocks_alloc, tr_se_pair_t* last_block)
{
  disk_err_t errno;

  __r2 = bytecount;
  __r6 = (uint16_t) tr_se_tab;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __BlkAlloc \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  *blocks_alloc = __r2;
  last_block->track = __r3L;
  last_block->sector = __r3H;
  
  return errno;
}

disk_err_t NxtBlkAlloc(tr_se_pair_t start_block, uint16_t bytecount, const tr_se_pair_t* tr_se_tab, uint16_t* blocks_alloc, tr_se_pair_t* last_block)
{
  disk_err_t errno;

  __r3L = start_block.track;
  __r3H = start_block.sector;
  __r2 = bytecount;
  __r6 = (uint16_t) tr_se_tab;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __NxtBlkAlloc \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  *blocks_alloc = __r2;
  last_block->track = __r3L;
  last_block->sector = __r3H;

  return errno;
}

disk_err_t SetNextFree(tr_se_pair_t start_block, tr_se_pair_t* alloc_block)
{
  disk_err_t errno;

  __r3L = start_block.track;
  __r3H = start_block.sector;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __SetNextFree \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  alloc_block->track = __r3L;
  alloc_block->sector = __r3H;
  
  return errno;
}

uint8_t FindBAMBit(tr_se_pair_t tr_se, uint8_t* bam_offset)
{
  uint8_t offs;
  uint8_t bits;

  __r6L = tr_se.track;
  __r6H = tr_se.sector;

  __attribute__((leaf)) 
  asm volatile("jsr __FindBAMBit " : "=x" (offs), "=a" (bits) : : "y","c","v");

  *bam_offset = offs;
  return bits;
}

disk_err_t FreeBlock(tr_se_pair_t tr_se)
{
  disk_err_t errno;

  __r6L = tr_se.track;
  __r6H = tr_se.sector;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FreeBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c", "v"
  );

  return errno;
}

disk_err_t SetGDirEntry(uint8_t dir_page, uint16_t num_blocks, const file_tr_se_tab_t* ts_tab, const file_header_t* file_header, tr_se_pair_t** first_block)
{
  disk_err_t errno;

  __r10L = dir_page;
  __r2 = num_blocks;
  __r6 = (uint16_t)ts_tab;
  __r9 = (uint16_t)file_header;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __SetGDirEntry \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  *first_block = (tr_se_pair_t*)__r6;
  return errno;
}

tr_se_pair_t* BldGDirEntry(uint16_t num_blocks, const file_tr_se_tab_t* ts_tab, const file_header_t* file_header)
{
  disk_err_t errno;

  __r2 = num_blocks;
  __r6 = (uint16_t)ts_tab;
  __r9 = (uint16_t)file_header;

  __attribute__((leaf)) asm volatile(
    "jsr __BldGDirEntry " : : : "a","x","y","c","v"
  );

  return (tr_se_pair_t*)__r6;
}

disk_err_t FollowChain(tr_se_pair_t start_block, file_tr_se_tab_t* ts_tab)
{
  disk_err_t errno;

  __r1L = start_block.track;
  __r1H = start_block.sector;
  __r3 = (uint16_t)ts_tab;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FollowChain \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;

}

disk_err_t FastDelFile(const char* file_name, file_tr_se_tab_t* ts_tab)
{
  disk_err_t errno;

  __r0 = (uint16_t)file_name;
  __r3 = (uint16_t)ts_tab;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FastDelFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t FreeFile(const dir_entry_t* buffer)
{
  disk_err_t errno;

  __r9 = (uint16_t)buffer;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __FreeFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

/***********************************************************************
 * GEOS Low-Level File Routines
 ***********************************************************************/

void InitForIO(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __InitForIO \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

void DoneWithIO(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __DoneWithIO \n"
    "jsr __swap_userzp " : : : "a","y","c","v"
  );
}

disk_err_t PurgeTurbo(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PurgeTurbo \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t EnterTurbo(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __EnterTurbo \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t ExitTurbo(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ExitTurbo \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t ReadBlock(tr_se_pair_t block_ts, disk_block_t* block_buffer)
{
  disk_err_t errno;

  __r1L = block_ts.track;
  __r1H = block_ts.sector;
  __r4 = (uint16_t)block_buffer;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t WriteBlock(tr_se_pair_t block_ts, const disk_block_t* block_buffer)
{
  disk_err_t errno;

  __r1L = block_ts.track;
  __r1H = block_ts.sector;
  __r4 = (uint16_t)block_buffer;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __WriteBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t VerWriteBlock(tr_se_pair_t block_ts, const disk_block_t* block_buffer)
{
  disk_err_t errno;

  __r1L = block_ts.track;
  __r1H = block_ts.sector;
  __r4 = (uint16_t)block_buffer;
  
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __VerWriteBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

/***********************************************************************
 * GEOS VLIR File Routines
 ***********************************************************************/

disk_err_t OpenRecordFile(const char* file_name)
{
  disk_err_t errno;

  __r0 = (uint16_t)file_name;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __OpenRecordFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t CloseRecordFile(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __CloseRecordFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t UpdateRecordFile(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __UpdateRecordFile \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t PreviousRecord(uint8_t* record_no, bool* is_empty)
{
  disk_err_t errno;
  bool empty;
  uint8_t rno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PreviousRecord \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (empty), "=a" (rno) : : "c","v"
  );
  
  *record_no = rno;
  *is_empty = !empty;

  return errno;
}

disk_err_t NextRecord(uint8_t* record_no, bool* is_empty)
{
  disk_err_t errno;
  bool empty;
  uint8_t rno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __NextRecord \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (empty), "=a" (rno) : : "c","v"
  );
  
  *record_no = rno;
  *is_empty = !empty;
  
  return errno;
}

disk_err_t PointRecord(uint8_t record_no, uint8_t* new_record_no, bool* is_empty)
{
  disk_err_t errno;
  bool empty;
  uint8_t new_rno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PointRecord \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (empty), "=a" (new_rno) : "a" (record_no) : "c","v"
  );
  
  *is_empty = !empty;  
  *new_record_no = new_rno;
  return errno;
}

disk_err_t DeleteRecord(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __DeleteRecord \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t WriteRecord(const uint8_t* data, uint16_t num_bytes)
{
  disk_err_t errno;

  __r2 = num_bytes;
  __r7 = (uint16_t)data;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __WriteRecord \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t ReadRecord(uint8_t* data, uint16_t num_bytes, bool* is_empty)
{
  disk_err_t errno;
  bool empty;

  __r2 = num_bytes;
  __r7 = (uint16_t)data;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadRecord \n"
    "jsr __swap_userzp " : "=x" (errno), "=a" (empty) : : "y","c","v"
  );

  *is_empty = !empty;
  return errno;
}

disk_err_t AppendRecord(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __AppendRecord \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

disk_err_t InsertRecord(void)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __InsertRecord \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

/***********************************************************************
 * GEOS Expansion RAM Routines
 ***********************************************************************/

uint8_t StashRAM(const uint8_t* cbm_source, uint8_t* reu_dest, uint16_t count, uint8_t reu_bank)
{
  disk_err_t errno;
  uint8_t reu_status;

  __r0 = (uint16_t)cbm_source;
  __r1 = (uint16_t)reu_dest;
  __r2 = count;
  __r3L = reu_bank;
  __attribute__((leaf)) asm volatile(
    "jsr __StashRAM " : "=x" (errno), "=a" (reu_status) : : "y","c","v"
  );

  if (errno != 0)
    return errno;
  else
    return reu_status;
}

uint8_t FetchRAM(const uint8_t* reu_source, uint8_t* cbm_dest, uint16_t count, uint8_t reu_bank)
{
  disk_err_t errno;
  uint8_t reu_status;

  __r0 = (uint16_t)cbm_dest;
  __r1 = (uint16_t)reu_source;
  __r2 = count;
  __r3L = reu_bank;
  __attribute__((leaf)) asm volatile(
    "jsr __FetchRAM \n" : "=x" (errno), "=a" (reu_status) : : "y","c","v"
  );

  if (errno != 0)
    return errno;
  else
    return reu_status;
}

uint8_t SwapRAM(uint8_t* cbm_addr, uint8_t* reu_addr, uint16_t count, uint8_t reu_bank)
{
  disk_err_t errno;
  uint8_t reu_status;

  __r0 = (uint16_t)cbm_addr;
  __r1 = (uint16_t)reu_addr;
  __r2 = count;
  __r3L = reu_bank;
  __attribute__((leaf)) asm volatile(
    "jsr __SwapRAM \n" : "=x" (errno), "=a" (reu_status) : : "y","c","v"
  );

  if (errno != 0)
    return errno;
  else
    return reu_status;
}

uint8_t VerifyRAM(const uint8_t* cbm_addr, const uint8_t* reu_addr, uint16_t count, uint8_t reu_bank)
{
  disk_err_t errno;
  uint8_t reu_status;

  __r0 = (uint16_t)cbm_addr;
  __r1 = (uint16_t)reu_addr;
  __r2 = count;
  __r3L = reu_bank;
  __attribute__((leaf)) asm volatile(
    "jsr __VerifyRAM \n" : "=x" (errno), "=a" (reu_status) : : "y","c","v"
  );

  if (errno != 0)
    return errno;
  else
    return reu_status;
}

uint8_t DoRAMOp(uint8_t* cbm_addr, uint8_t* reu_addr, uint16_t count, uint8_t reu_bank, uint8_t cmd)
{
  disk_err_t errno;
  uint8_t reu_status;

  __r0 = (uint16_t)cbm_addr;
  __r1 = (uint16_t)reu_addr;
  __r2 = count;
  __r3L = reu_bank;
  __attribute__((leaf)) asm volatile(
    "jsr __DoRAMOp \n" : "=x" (errno), "=a" (reu_status) : "a"  (cmd) : "y","c","v"
  );

  if (errno != 0)
    return errno;
  else
    return reu_status;
}

/***********************************************************************
 * GEOS Printing Routines
 ***********************************************************************/

void InitForPrint(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr _InitForPrint \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

void PrintBuffer(const uint8_t* print_data, uint8_t* work_buf, const uint8_t* color_data)
{
  __r0 = (uint16_t)print_data;
  __r1 = (uint16_t)work_buf;
  __r2 = (uint16_t)color_data;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PrintBuffer \n" 
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

void StopPrint(uint8_t* temp_buf, uint8_t* work_buf)
{
  __r0 = (uint16_t)temp_buf;
  __r1 = (uint16_t)work_buf;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __StopPrint \n" 
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

uint8_t GetDimensions(uint8_t* cards_wide, uint8_t* cards_height)
{
  uint8_t modes;
  uint8_t w, h;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetDimensions \n" 
    "jsr __swap_userzp " : "=a" (modes), "=x" (w), "=y" (h) : : "c","v"
  );

  *cards_wide = w;
  *cards_height = h;
  return modes;
}

void PrintASCII(const char* print_data, uint8_t* work_buf)
{
  __r0 = (uint16_t)print_data;
  __r1 = (uint16_t)work_buf;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __PrintASCII \n" 
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

uint8_t StartASCII(uint8_t* work_buf)
{
  uint8_t errno;

  __r1 = (uint16_t)work_buf;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __StartASCII \n" 
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );

  return errno;
}

void SetNLQ(uint8_t* work_buf)
{
  __r1 = (uint16_t)work_buf;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __SetNLQ \n"
    "jsr __swap_userzp " : : : "a","x","y","c","v"
  );
}

/***********************************************************************
 * Only in GEOS 128
 ***********************************************************************/

void TempHideMouse(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __TempHideMouse " : : : "a","x","c","v"
  );
}

void HideOnlyMouse(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __HideOnlyMouse " : : : "a","x","y","c","v"
  );
}

void SetNewMode(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __TempHideMouse " : : : "a","x","y","c","v"
  );
}

uint16_t NormalizeX(uint16_t x)
{
  __r0 = x;

  __attribute__((leaf)) asm volatile(
    "ldx #2 \n"
    "jsr __NormalizeX " : : : "a","x","c","v"
  );

  return __r0;
}

void MoveBData(const uint8_t* source, uint8_t* dest, uint16_t count, uint8_t src_bank, uint8_t dst_bank)
{
  __r0 = (uint16_t)source;
  __r1 = (uint16_t)dest;
  __r2 = count;
  __r3L = src_bank;
  __r3H = dst_bank;

  __attribute__((leaf)) asm volatile(
    "jsr __MoveBData " : : : "a","x","y","c","v"
  );
}

void SwapBData(uint8_t* addr1, uint8_t* addr2, uint16_t count, uint8_t a1_bank, uint8_t a2_bank)
{
  __r0 = (uint16_t)addr1;
  __r1 = (uint16_t)addr2;
  __r2 = count;
  __r3L = a1_bank;
  __r3H = a2_bank;

  __attribute__((leaf)) asm volatile(
    "jsr __SwapBData " : : : "a","x","y","c","v"
  );
}

uint8_t VerifyBData(uint8_t* addr1, uint8_t* addr2, uint16_t count, uint8_t a1_bank, uint8_t a2_bank)
{
  uint8_t status;

  __r0 = (uint16_t)addr1;
  __r1 = (uint16_t)addr2;
  __r2 = count;
  __r3L = a1_bank;
  __r3H = a2_bank;

  __attribute__((leaf)) asm volatile(
    "jsr __VerifyBData" : "=x" (status) : : "a","y","c","v"
  );

  return status;
}

uint8_t DoBOp(uint8_t* addr1, uint8_t* addr2, uint16_t count, uint8_t a1_bank, uint8_t a2_bank, uint8_t mode)
{
  uint8_t status;

  __r0 = (uint16_t)addr1;
  __r1 = (uint16_t)addr2;
  __r2 = count;
  __r3L = a1_bank;
  __r3H = a2_bank;

  __attribute__((leaf)) asm volatile(
    "jsr __DoBOp" : "=x" (status) : "y" (mode) : "a","c","v"
  );

  return status;
}

uint8_t AccessCache(uint8_t block_no, uint8_t* buffer, uint8_t mode, uint8_t* verify_result)
{
  uint8_t ver;
  uint8_t block_valid, unused;

  __r1H = block_no;
  __r4 = (uint16_t)buffer;

  __attribute__((leaf)) asm volatile(
    "                 jsr __AccessCache \n" 
    "                 beq __cache_valid \n"
    "                 ldx #0xff \n"
    "                 bne __cache_done \n"
    "__cache_valid:   ldx #0x00 \n"
    "__cache_done: "
    : "=a" (ver), "=x" (block_valid), "=y" (unused) : "y" (mode) : "c","v"
  );

  *verify_result = ver;
  return block_valid;

}

void SetColorMode(uint8_t clr_mode)
{
  __attribute__((leaf)) 
  asm volatile("jsr __SetColorMode" : "=a" (clr_mode) : "a" (clr_mode) : "x","y","c","v");
}

void SetColorCard(uint16_t x, uint8_t y, uint8_t color)
{
  __r3 = x;
  __r11L = y;
  __attribute__((leaf)) asm volatile(
    "sec \n"
    "jsr __ColorCard " : : "a" (color) : "x","y","c","v");
}

uint8_t GetColorCard(uint16_t x, uint8_t y)
{
  uint8_t color;

  __r3 = x;
  __r11L = y;

  __attribute__((leaf)) asm volatile(
    "clc \n"
    "jsr __ColorCard " : "=a" (color) : : "x","y","c","v");

  return color;
}

void ColorRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom, uint8_t fbcolor)
{
  __r2L = top;
  __r3L = bottom;
  __r3 = left;
  __r3 = right;

  __attribute__((leaf)) asm volatile("jsr __ColorCard " : "=a" (fbcolor) : "a" (fbcolor) : "x","y","c","v");
}

disk_err_t Get1stDirEntry(dir_entry_t** dir_entry)
{
  disk_err_t errno;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __Get1stDirEntry \n"
    "jsr __swap_userzp " : "=x" (errno): : "a","y","c","v"
  );
  
  *dir_entry = (dir_entry_t*)__r5;
  return errno;
}

disk_err_t GetNxtDirEntry(dir_entry_t** dir_entry, bool* end_of_dir)
{
  disk_err_t errno;
  bool eod;

  __r5 = (uint16_t)*dir_entry;
  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetNxtDirEntry \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (eod) : : "a","c","v"
  );
  
  *dir_entry = (dir_entry_t*)__r5;
  *end_of_dir = eod;
  
  return errno;
}

disk_err_t GetOffPageTrSc(bool* no_geos_disk, tr_se_pair_t* border_block)
{
  disk_err_t errno;
  bool no_geos;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __GetOffPageTrSc \n"
    "jsr __swap_userzp " : "=x" (errno), "=y" (no_geos) : : "a","c","v"
  );
  
  *no_geos_disk = no_geos;
  border_block->track = __r1L;
  border_block->sector = __r1H;

  return errno;
}

disk_err_t AllocateBlock(tr_se_pair_t block_addr)
{
  disk_err_t errno;

  __r6L = block_addr.track;
  __r6H = block_addr.sector;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __AllocateBlock \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );
  
  return errno;
}

disk_err_t ReadLink(tr_se_pair_t block_addr, uint8_t* buffer)
{
  disk_err_t errno;

  __r1L = block_addr.track;
  __r1H = block_addr.sector;
  __r4 = (uint16_t)buffer;

  __attribute__((leaf)) asm volatile(
    "jsr __swap_userzp \n"
    "jsr __ReadLink \n"
    "jsr __swap_userzp " : "=x" (errno) : : "a","y","c","v"
  );
  
  return errno;
}

void MainLoop(void)
{
  __attribute__((leaf)) asm volatile(
    "jsr __MainLoop " : : : "a","x","y","c","v"
  );
}