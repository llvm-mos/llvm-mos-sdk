#ifndef _SIM_STDLIB_H_
#define _SIM_STDLIB_H_

#include_next <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned long clock();
void reset_clock();

#ifdef __cplusplus
}
#endif

#endif // not _SIM_STDLIB_H_
