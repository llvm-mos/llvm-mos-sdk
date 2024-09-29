/********************************************************************
 * SamVlirEdit.c
 *
 * This file contains the Edit Module code for the llvm-mos GEOS VLIR
 * sample application.
 *
 ********************************************************************/

#include <geos.h>

#include "SamVlir.h"

/* Through this pragma all functions and module data will be stored in VLIR 2
 * record. */

#pragma clang section text = ".vlir02.text" data = ".vlir02.data" bss =        \
    ".vlir02.bss"

/* Dialog box to indicate that an event handler funnction was called. */
/* Parameter 2 of DB_NAME_SECT sets the vlir record 2 */

DB_NAME_SECT(dlg_edit, vlir02)
DB_DEFPOS(1)
DB_ICON(OK, DBI_X_0, DBI_Y_2)
DB_VARSTR(DBI_X_0, DBI_Y_0, __r15)
DB_END(dlg_edit)

/* Define string constants as static variables. This way they will be stored
 * in the vlir record 2 and not in the main constant string pool.
 */

char cut_msg[] = "cut handler called.";
char copy_msg[] = "copy handler called.";
char paste_msg[] = "paste handler called.";
char icon1_msg[] = "icon handler called.";

/********************************************************************
 * This is a dummy event handler function. Customize this for your
 * own application. The noinline decorator guarantees that the
 * function is stored in the VLIR 2 record and that the optimier
 * will not inline the code in the main (VLIR 0) record.
 ********************************************************************/

__attribute__((noinline)) void DoCut(void) {
  __r15 = (uint16_t)cut_msg;
  DoDlgBox(dlg_edit);
}

/********************************************************************
 * This is a dummy event handler function. Customize this for your
 * own application. The noinline decorator guarantees that the
 * function is stored in the VLIR 2 record and that the optimier
 * will not inline the code in the main (VLIR 0) record.
 ********************************************************************/

__attribute__((noinline)) void DoCopy(void) {
  __r15 = (uint16_t)copy_msg;
  DoDlgBox(dlg_edit);
}

/********************************************************************
 * This is a dummy event handler function. Customize this for your
 * own application. The noinline decorator guarantees that the
 * function is stored in the VLIR 2 record and that the optimier
 * will not inline the code in the main (VLIR 0) record.
 ********************************************************************/

__attribute__((noinline)) void DoPaste(void) {
  __r15 = (uint16_t)paste_msg;
  DoDlgBox(dlg_edit);
}

/********************************************************************
 * This is a dummy event handler function. Customize this for your
 * own application. The noinline decorator guarantees that the
 * function is stored in the VLIR 2 record and that the optimier
 * will not inline the code in the main (VLIR 0) record.
 ********************************************************************/

__attribute__((noinline)) void DoIcon1(void) {
  __r15 = (uint16_t)icon1_msg;
  DoDlgBox(dlg_edit);
}
