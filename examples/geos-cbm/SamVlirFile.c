/********************************************************************
 * SamVlirFile.c
 *
 * This file contains the File Module code for the llvm-mos GEOS VLIR
 * sample application.
 *
 ********************************************************************/

#include <geos.h>

#include "SamVlir.h"

/* Through this pragma all functions and module data will be stored in VLIR 1
 * record. */

#pragma clang section text = ".vlir01.text" data = ".vlir01.data" bss =        \
    ".vlir01.bss"

/********************************************************************
 * This function loads and runs a desk accessory. Note that the call
 * to GetFile to load the desk accessory causes the memory under the
 * desk accessory to be swapped out and control transfered to the desk
 * accessory. When the desk accessory is "turned off" by executing a
 * call to RstrAppl, control returns to the application (in this case
 * the deskTop) immediatly following the call to GetFile.
 * The noinline decorator tells the optimizer to keep the code in
 * VLIR 1 record and to not inline it into the main (VLIR 0) record.
 ********************************************************************/

uint8_t spriteBuf[7 * 64];

__attribute__((noinline)) void RunDA(uint8_t da_index) {

  /* place code that will run before a desk accessory here */

  /* close any open VLIR files */

  /* copy sprite picture data (for 7 sprites) to a buffer */
  MoveData(&sprpic[1], spriteBuf, sizeof(spriteBuf));

  /* save sprites double-Y flag in case is changed by desk accessory */
  uint8_t old_cpu_data = CPU_DATA;
  CPU_DATA = IO_IN;
  uint8_t old_moby2 = moby2;
  moby2 = 0;
  CPU_DATA = old_cpu_data;

  disk_err_t err = GetFile(DAText[da_index], 0b00000000, 0, 0, 0, 0);

  /* At this point GEOS saves
   * - pointers to menu and icon structures
   * - all sprite x, y, color and doubleX info
   *
   * desk accessory code must:
   * - set its own sprite pictures and doubleXY information
   * - set the desired screen colors (40-column mode only)
   * - not use 0x0200-0x03ff for variables, because some new
   *   applications (geoFile, geoDebug) do
   *
   * when desk accessory has finished, GEOS restores:
   * - pointers to menu and icon structures
   * - all sprite x, y, color and doubleX info
   * -
   */

  /* restore sprite´s double-y flag in case it was changed by the desk accessory
   */
  old_cpu_data = CPU_DATA;
  CPU_DATA = IO_IN;
  moby2 = old_moby2;
  CPU_DATA = old_cpu_data;

  /* restore sprite picture data */
  MoveData(spriteBuf, &sprpic[1], 7 * 64);

  /* since we did not have DA save our foreground screen,
   * must recover from background here */
  FillRam((void *)COLOR_MATRIX, 25 * 40, screencolors);

  /* since we did not have DA save our foreground screen,
   * must recover from background here. */
  RecoverRectangle(0, MM_BOTTOM + 1, 319, 199);

  if (err != 0) {
    /* handle disk errors here */
  }

  /* code to run after desk accessory completion goes here */

  /* re-open VLIR files here */
}

/* define string on file level so that it is stored in VLIR record 1. */

char close_msg[] = "close handler called.";

/* Dialog box to indicate that close handler function was called. */

DB_NAME_SECT(dlgClose, vlir01)
DB_DEFPOS(1)
DB_ICON(OK, DBI_X_0, DBI_Y_2)
DB_TXTSTR(DBI_X_0, DBI_Y_0, close_msg)
DB_END(dlgClose)

__attribute__((noinline)) void DoClose(void) { DoDlgBox(dlgClose); }
