/***********************************************************************
 * geos_routines.h
 *
 * This file contains symbol definitions for use in GEOS applications
 * with llvm-mos C compiler.
 *
 * Transcribed from geoProgrammer manual by DiSc.
 *
 ***********************************************************************/

/***********************************************************************
 * Jump addresses within printer drivers
 ***********************************************************************/
void InitForPrint(void);
uint8_t StartPrint(uint8_t *work_buf);
void PrintBuffer(const uint8_t *print_data, uint8_t *work_buf,
                 const uint8_t *color_data);
void StopPrint(uint8_t *temp_buf, uint8_t *work_buf);
uint8_t GetDimensions(uint8_t *cards_wide, uint8_t *cards_height);
void PrintASCII(const char *print_data, uint8_t *work_buf);
uint8_t StartASCII(uint8_t *work_buf);
void SetNLQ(uint8_t *work_buf);

/***********************************************************************
 * Jump addresses within disk drivers: these are only valid for non-1541
 * disk drive types, and for the 128 versions of the 1541 driver.
 ***********************************************************************/
disk_err_t Get1stDirEntry(dir_entry_t **dir_entry);
disk_err_t GetNxtDirEntry(dir_entry_t **dir_entry, bool *end_of_dir);
disk_err_t GetOffPageTrSc(bool *no_geos_disk, tr_se_pair_t *border_block);
disk_err_t AllocateBlock(tr_se_pair_t block_addr);
disk_err_t ReadLink(tr_se_pair_t block_addr, uint8_t *buffer);

/** undocumented Official and Hitchhikers Guides
extern void __AddDirBlock(void);
extern void __ReadBuff(void);
extern void __WriteBuff(void);
extern void __SendTSBytes(void);
extern void __CheckErrors(void); */

/***********************************************************************
 * Graphics Routines
 ***********************************************************************/
void HorizontalLine(uint16_t left, uint16_t right, uint8_t y, uint8_t pattern);
void InvertLine(uint16_t left, uint16_t right, uint8_t y);
void RecoverLine(uint16_t left, uint16_t right, uint8_t y);
void VerticalLine(uint16_t x, uint8_t top, uint8_t bottom, uint8_t pattern);
void Rectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom);
void FrameRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom,
                    uint8_t pattern);
void InvertRectangle(uint16_t left, uint8_t top, uint16_t right,
                     uint8_t bottom);
void RecoverRectangle(uint16_t left, uint8_t top, uint16_t right,
                      uint8_t bottom);
void DrawLine(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom,
              bool recover, bool background);
void DrawPoint(uint16_t x, uint8_t y, bool recover, bool foreground);
void SetPattern(uint8_t pattern);
bool TestPoint(uint16_t x, uint8_t y);
void ImprintRectangle(uint16_t left, uint8_t top, uint16_t right,
                      uint8_t bottom);
void BitmapUp(const uint8_t *bitmap, uint8_t card_left, uint8_t top,
              uint8_t card_width, uint8_t height);
void BitmapClip(const uint8_t *bitmap, uint8_t card_left, uint8_t top,
                uint8_t card_width, uint8_t height, uint8_t left_skip,
                uint8_t right_skip, uint16_t top_skip);
void BitOtherClip(const uint8_t *bitmap, uint8_t card_left, uint8_t top,
                  uint8_t card_width, uint8_t height, uint8_t left_skip,
                  uint8_t right_skip, uint16_t top_skip, vector app_input,
                  vector sync);
void GraphicsString(const uint8_t *graph_string);
void GetScanLine(uint8_t scanline, uint16_t *first_screen_byte,
                 uint16_t *first_backgr_byte);

/***********************************************************************
 * Character Manipulation Routines
 ***********************************************************************/
void PutString(uint16_t x, uint8_t y, const char *str);
void PutDecimal(uint16_t value, uint16_t x, uint8_t y, uint8_t format);
uint8_t GetString(char *buffer, uint16_t x, uint8_t y, uint8_t max_chars,
                  vector fault);

char GetNextChar(void);
void InitTextPrompt(uint8_t height);
void PromptOn(void);
void PromptOff(void);
uint16_t PutChar(uint16_t x, uint8_t y, char ch);
uint16_t SmallPutChar(uint16_t x, uint8_t y, char ch);
void GetRealSize(char ch, uint8_t mode, uint8_t *width, uint8_t *height,
                 uint8_t *baseline_offset);
uint8_t GetCharWidth(char ch);
void LoadCharSet(uint8_t *font_info_tab);
void UseSystemFont(void);

/***********************************************************************
 * Jump addresses within input drivers for C64
 ***********************************************************************/
void InitMouse(void);
void SlowMouse(void);
void UpdateMouse(void);
void SetMouse(void);
/** for C128 */
void MouseInit_128(void);
void SlowMouse_128(void);
void UpdateMouse_128(void);
void SetMouse_128(void);

/***********************************************************************
 * Mouse related routines
 ***********************************************************************/
void StartMouseMode(uint16_t x, uint8_t y);
void ClearMouseMode(void);
void MouseOff(void);
void MouseUp(void);
bool IsMseInRegion(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom);

/***********************************************************************
 * Dialog Box Routines
 ***********************************************************************/
uint8_t DoDlgBox(uint8_t *dlg_table);
void RstrFrmDialog(uint8_t icon_no);

/***********************************************************************
 * Routines for menus and icons
 ***********************************************************************/
void DoMenu(const menu_tab_t *menu_table, uint8_t selected_menu_no);
void DoPreviousMenu(void);
void ReDoMenu(void);
void RecoverMenu(void);
void RecoverAllMenus(void);
void GotoFirstMenu(void);

void DoIcons(const icon_table_t *icon_table);

/***********************************************************************
 * Routines for Sprite Support
 ***********************************************************************/
void DrawSprite(uint8_t sprite_no, const uint8_t *sprite_data);
void PosSprite(uint8_t sprite_no, uint16_t x, uint8_t y);
void EnablSprite(uint8_t sprite_no);
void DisablSprite(uint8_t sprite_no);

/***********************************************************************
 * Routines for Process Support
 ***********************************************************************/
void InitProcesses(uint8_t num_of_processes, const uint8_t *process_table);
void RestartProcess(uint8_t process_num);
void BlockProcess(uint8_t process_num);
void UnlockProcess(uint8_t process_num);
void FreezeProcess(uint8_t process_num);
void UnfreezeProcess(uint8_t process_num);
void Sleep(uint16_t jiffies);
void EnableProcess(uint8_t process_num);

/***********************************************************************
 * Utitlity & General Library Routines
 ***********************************************************************/
uint16_t GetRandom(void);
void CopyString(char *src, char *dest);
void CopyFString(uint8_t *src, uint8_t *dest, uint8_t count);
int8_t CmpString(char *src, char *dest);
int8_t CmpFString(char *src, char *dest, uint8_t count);
void Panic(void);
void MoveData(const void *src, void *dest, uint16_t count);
void ClearRam(void *memory, uint16_t count);
void FillRam(void *memory, uint16_t count, uint8_t value);
void InitRam(uint8_t *init_table);
uint16_t GetSerialNumber(void);
void ToBasic(uint8_t *basic_cmd);
void EnterDeskTop(void);
void FirstInit(void);
uint16_t CRC(uint8_t *data, uint16_t count);

/***********************************************************************
 * High Level File Routines
 ***********************************************************************/
disk_err_t SetDevice(uint8_t device);
disk_err_t OpenDisk(char **disk_name);
void GetPtrCurDkNm(disk_name_t buffer);
disk_err_t SetGEOSDisk(void);
bool ChkDkGEOS(dir_header_t *dir_header);
uint8_t FindFTypes(char file_names[][17], geos_file_type_t file_type,
                   uint8_t max_filenames, const char *permanent_name);
disk_err_t GetFile(const char *file_name, uint8_t loadOptFlg,
                   const char *disk_name, const char *data_file,
                   uint8_t *load_addr, uint8_t daRecFlg);
disk_err_t FindFile(const char *file_name, tr_se_pair_t *tr_se,
                    dir_entry_t *dir_entry);
disk_err_t SaveFile(file_header_block_t *header_block, uint8_t dir_page);
disk_err_t DeleteFile(const char *file_name);
disk_err_t RenameFile(const char *old_name, const char *new_name);
uint16_t CalcBlksFree(dir_header_t *dir_header, uint16_t *total_blocks);

/***********************************************************************
 * Intermediate Level File Routines
 ***********************************************************************/
disk_err_t GetBlock(tr_se_pair_t tr_se, disk_block_t *disk_block);
disk_err_t PutBlock(tr_se_pair_t tr_se, const disk_block_t *disk_block);
disk_err_t GetFHdrInfo(const dir_entry_t *dir_entry, tr_se_pair_t *tr_se,
                       uint8_t **load_addr);
disk_err_t ReadFile(uint8_t *buffer, uint16_t length, tr_se_pair_t tr_se);
disk_err_t WriteFile(const uint8_t *buffer, tr_se_pair_t *blocks);
disk_err_t ReadByteInit(tr_se_pair_t tr_se, disk_block_t *buffer,
                        uint8_t *value);
disk_err_t ReadByteNext(uint8_t *value);
disk_err_t GetDirHead(void);
disk_err_t PutDirHead(void);
disk_err_t NewDisk(void);
disk_err_t LdApplic(dir_entry_t *dir_entry, uint8_t loadOptFlg,
                    const char *disk_name, const char *data_file,
                    uint8_t *load_addr);
void RstrAppl(void);
disk_err_t LdDescAcc(dir_entry_t *dir_entry);
disk_err_t LdFile(dir_entry_t *dir_entry);
disk_err_t StartAppl(uint8_t loadOptFlg, const char *disk_name,
                     const char *data_file, uint8_t *start_addr);
disk_err_t GetFreeDirBlk(uint8_t dir_page_no, uint8_t *free_entry_idx,
                         uint8_t *page_no);
disk_err_t BlkAlloc(uint16_t bytecount, const tr_se_pair_t *tr_se_tab,
                    uint16_t *blocks_alloc, tr_se_pair_t *last_block);
disk_err_t NxtBlkAlloc(tr_se_pair_t start_block, uint16_t bytecount,
                       const tr_se_pair_t *tr_se_tab, uint16_t *blocks_alloc,
                       tr_se_pair_t *last_block);
uint8_t FindBAMBit(tr_se_pair_t tr_se, uint8_t *bam_offset);
disk_err_t FreeBlock(tr_se_pair_t tr_se);
disk_err_t SetGDirEntry(uint8_t dir_page, uint16_t num_blocks,
                        const file_tr_se_tab_t *ts_tab,
                        const file_header_t *file_header,
                        tr_se_pair_t **first_block);
tr_se_pair_t *BldGDirEntry(uint16_t num_blocks, const file_tr_se_tab_t *ts_tab,
                           const file_header_t *file_header);
disk_err_t FollowChain(tr_se_pair_t start_block, file_tr_se_tab_t *ts_tab);
disk_err_t FastDelFile(const char *file_name, file_tr_se_tab_t *ts_tab);
disk_err_t FreeFile(const dir_entry_t *buffer);

/***********************************************************************
 * Low Level File Routines
 ***********************************************************************/
void InitForIO(void);
void DoneWithIO(void);
disk_err_t PurgeTurbo(void);
disk_err_t EnterTurbo(void);
disk_err_t ExitTurbo(void);
disk_err_t ReadBock(tr_se_pair_t block_ts, disk_block_t *block_buffer);
disk_err_t WriteBock(tr_se_pair_t block_ts, const disk_block_t *block_buffer);
disk_err_t VerWriteBock(tr_se_pair_t block_ts,
                        const disk_block_t *block_buffer);

/***********************************************************************
 * VLIR Level File Routines
 ***********************************************************************/
disk_err_t OpenRecordFile(const char *file_name);
disk_err_t CloseRecordFile(void);
disk_err_t UpdateRecordFile(void);
disk_err_t PreviousRecord(uint8_t *record_no, bool *is_empty);
disk_err_t NextRecord(uint8_t *record_no, bool *is_empty);
disk_err_t PointRecord(uint8_t record_no, uint8_t *new_record_no,
                       bool *is_empty);
disk_err_t WriteRecord(const uint8_t *data, uint16_t num_bytes);
disk_err_t ReadRecord(uint8_t *data, uint16_t num_bytes, bool *is_empty);
disk_err_t AppendRecord(void);
disk_err_t InsertRecord(void);
disk_err_t DeleteRecord(void);

/***********************************************************************
 * RAM Expansion Routines
 ***********************************************************************/
uint8_t StashRAM(const uint8_t *cbm_source, uint8_t *reu_dest, uint16_t count,
                 uint8_t reu_bank);
uint8_t FetchRAM(const uint8_t *reu_source, uint8_t *cbm_dest, uint16_t count,
                 uint8_t reu_bank);
uint8_t SwapRAM(uint8_t *cbm_addr, uint8_t *reu_addr, uint16_t count,
                uint8_t reu_bank);
uint8_t VerifyRAM(const uint8_t *cbm_addr, const uint8_t *reu_addr,
                  uint16_t count, uint8_t reu_bank);
uint8_t DoRAMOp(uint8_t *cbm_addr, uint8_t *reu_addr, uint16_t count,
                uint8_t reu_bank, uint8_t cmd);

/***********************************************************************
 * only in GEOS 128
 ***********************************************************************/

/** GEOS 128 Back-RAM Routines */
void MoveBData(const uint8_t *source, uint8_t *dest, uint16_t count,
               uint8_t src_bank, uint8_t dst_bank);
void SwapBData(uint8_t *addr1, uint8_t *addr2, uint16_t count, uint8_t a1_bank,
               uint8_t a2_bank);
uint8_t DoBOp(uint8_t *addr1, uint8_t *addr2, uint16_t count, uint8_t a1_bank,
              uint8_t a2_bank, uint8_t mode);

/** GEOS 128 additional Routines */
void TempHideMouse(void);
void HideOnlyMouse(void);
void SetNewMode(void);
uint16_t NormalizeX(uint16_t x);
uint8_t AccessCache(uint8_t block_no, uint8_t *buffer, uint8_t mode,
                    uint8_t *verify_result);
void SetColorMode(uint8_t clr_mode);
void SetColorCard(uint16_t x, uint8_t y, uint8_t color);
uint8_t GetColorCard(uint16_t x, uint8_t y);
void ColorRectangle(uint16_t left, uint8_t top, uint16_t right, uint8_t bottom,
                    uint8_t fbcolor);

void MainLoop(void);
