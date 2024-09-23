/********************************************************************
 * SamVlirRes.c
 *
 * This is the main file for the llvm-mos GEOS VLIR sample
 * application. It contains all the code and data required for the
 * resident portion of the program.
 *
 ********************************************************************/

#include <geos.h>

#include "SamVlir.h"

char DAText[8][17] = {"desk accessory 0", "desk accessory 1",
                      "desk accessory 2", "desk accessory 3",
                      "desk accessory 4", "desk accessory 5",
                      "desk accessory 6", "desk accessory 7"};

uint8_t ClearScreen[] = {NEWPATTERN,  2,         MOVEPENTO, WORD(0), 0,
                         RECTANGLETO, WORD(319), 199,       0};

/* holds currently swapped in module number */
uint8_t curModule;

/* holds (T,S) pairs, one for each module of our application */
tr_se_pair_t swapTable[NUM_MODS];

/*********************************************************************
 * This routine sets up a table which contains the track and sector
 * numbers for each of the program modules which can be loaded.
 * This table will be used by the SwapMod function later on.
 *********************************************************************/

void InitSwap(void) {
  char appName[1][17];

  FindFTypes(appName, APPLICATION, 1, "Sample VLIR V1.0");
  OpenRecordFile(appName[0]);
  MoveData((const uint8_t *)&fileHeader + 4, (uint8_t *)swapTable,
           NUM_MODS * 2);
  CloseRecordFile();
  curModule = 0xff;
}

/*********************************************************************
 * This routine swaps a module in. Note how it used "ReadFile" instead
 * of "ReadRecord" so that it does not affect any opened VLIR file.
 *********************************************************************/

__attribute__((noinline)) void SwapMod(uint8_t req_mod_no) {
  if (req_mod_no != curModule) {
    curModule = req_mod_no;
    ReadFile(OVERLAYADDR, OVERLAYSIZE, swapTable[req_mod_no - 1]);
  }
}

__attribute__((noinline)) void FileIn() { SwapMod(MOD_FILE); }

__attribute__((noinline)) void EditIn() { SwapMod(MOD_EDIT); }

__attribute__((noinline)) void R_DoAbout(void) { GotoFirstMenu(); }

__attribute__((noinline)) void R_RunDA(uint8_t da_idx) {
  GotoFirstMenu();
  FileIn();
  RunDA(da_idx);
}

void R_RunDA0(void) { R_RunDA(0); }
void R_RunDA1(void) { R_RunDA(1); }
void R_RunDA2(void) { R_RunDA(2); }
void R_RunDA3(void) { R_RunDA(3); }
void R_RunDA4(void) { R_RunDA(4); }
void R_RunDA5(void) { R_RunDA(5); }
void R_RunDA6(void) { R_RunDA(6); }
void R_RunDA7(void) { R_RunDA(7); }

void R_DoClose(void) {
  GotoFirstMenu();
  FileIn();
  DoClose();
}

void R_DoQuit(void) {
  GotoFirstMenu();
  EnterDeskTop();
}

void R_DoCut(void) {
  GotoFirstMenu();
  EditIn();
  DoCut();
}

void R_DoCopy(void) {
  GotoFirstMenu();
  EditIn();
  DoCopy();
}

void R_DoPaste(void) {
  GotoFirstMenu();
  EditIn();
  DoPaste();
}

void R_DoIcon1(void) {
  EditIn();
  DoIcon1();
}

/* Note the GEOS sub-menu as it appears below is constructed assuming
 * only 1 item - them "SampleVLir info" item. When then application is
 * started, a routine called "InitDA" will update the structure according
 * to the number of desk accessories found on the application disk.
 */

menu_tab_t GeosSubMenu = {.top = SM_TOP,
                          .bot = SM_TOP + 1 + 1 * 14,
                          .left = GM_LEFT,
                          .right = GM_LEFT + GM_WIDTH,
                          .menu_type_and_count = VERTICAL | GM_COUNT,
                          .items = {
                              {.text = "Sample VLIR info",
                               .action_type = MENU_ACTION,
                               .handler_function = R_DoAbout},
                              {.text = DAText[0],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA0},
                              {.text = DAText[1],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA1},
                              {.text = DAText[2],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA2},
                              {.text = DAText[3],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA3},
                              {.text = DAText[4],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA4},
                              {.text = DAText[5],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA5},
                              {.text = DAText[6],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA6},
                              {.text = DAText[7],
                               .action_type = MENU_ACTION,
                               .handler_function = R_RunDA7},
                          }};

menu_tab_t FileSubMenu = {.top = SM_TOP,
                          .bot = SM_TOP + 1 + FM_COUNT * 14,
                          .left = FM_LEFT,
                          .right = FM_LEFT + FM_WIDTH,
                          .menu_type_and_count = VERTICAL | FM_COUNT,
                          .items = {{.text = "close",
                                     .action_type = MENU_ACTION,
                                     .handler_function = R_DoClose},
                                    {.text = "quit",
                                     .action_type = MENU_ACTION,
                                     .handler_function = R_DoQuit}}};

menu_tab_t EditSubMenu = {.top = SM_TOP,
                          .bot = SM_TOP + 1 + EM_COUNT * 14,
                          .left = EM_LEFT,
                          .right = EM_LEFT + EM_WIDTH,
                          .menu_type_and_count = VERTICAL | EM_COUNT,
                          .items = {{.text = "cut",
                                     .action_type = MENU_ACTION,
                                     .handler_function = R_DoCut},
                                    {.text = "copy",
                                     .action_type = MENU_ACTION,
                                     .handler_function = R_DoCopy},
                                    {.text = "paste",
                                     .action_type = MENU_ACTION,
                                     .handler_function = R_DoPaste}}};

menu_tab_t MenuTable = {
    .top = MM_TOP,
    .bot = MM_BOTTOM,
    .left = MM_LEFT,
    .right = MM_RIGHT,
    .menu_type_and_count = MM_COUNT | HORIZONTAL,
    .items = {
        {.text = "geos", .action_type = VERTICAL, .sub_menu = &GeosSubMenu},
        {.text = "file", .action_type = VERTICAL, .sub_menu = &FileSubMenu},
        {.text = "edit", .action_type = VERTICAL, .sub_menu = &EditSubMenu}}};

uint8_t Icon1Picture[] = {
    /*
    ** This data was generated by sp65 2.17 - Debian 2.17-1 from
    ** icon.pcx (48x16, 2 colors, indexed)
    */
    0x13, 0x00, 0x81, 0x08, 0x05, 0x00, 0x81, 0x08, 0x05, 0x00, 0x8F,
    0x08, 0x30, 0x62, 0xC0, 0x00, 0x00, 0x08, 0x81, 0x12, 0x20, 0x00,
    0x00, 0x08, 0x81, 0x02, 0x03, 0x00, 0x83, 0x08, 0x81, 0x02, 0x03,
    0x00, 0x83, 0x08, 0x81, 0x02, 0x03, 0x00, 0x83, 0x08, 0x81, 0x12,
    0x03, 0x00, 0x83, 0x08, 0x30, 0x62, 0x1A, 0x00,
};
#define ICON1_WIDTH (48 / 8)
#define ICON1_HEIGHT 16

icon_table_t IconTable = {.num_icons = 1,
                          .mouse_x = 0,
                          .mouse_y = 0,
                          .icons = {{.graphic_data = Icon1Picture,
                                     .left = 3,
                                     .top = 60,
                                     .width = ICON1_WIDTH,
                                     .height = ICON1_HEIGHT,
                                     .service_routine = R_DoIcon1}}};

/*********************************************************************
 * This routine builds out the GEOS menu table so that it contains
 * the names of the desk accessories on the disk. Also see the RunDA
 * function.
 *********************************************************************/

void InitDA(void) {
  FindFTypes(DAText, DESK_ACC, NUM_DA, 0);

  uint8_t num_found = NUM_DA - __r7H;
  if (num_found != 0) {
    num_found++;
    GeosSubMenu.menu_type_and_count = num_found | VERTICAL;
    GeosSubMenu.bot = num_found * 14 + SM_TOP + 1;
  }
}

int main(void) {
  dispBufferOn = (ST_WR_FORE | ST_WR_BACK);
  GraphicsString(ClearScreen);

  InitSwap();
  InitDA();

  DoMenu(&MenuTable, 0);
  DoIcons(&IconTable);

  MainLoop();

  return 0;
}
