#ifndef _SIM_STDLIB_H_
#define _SIM_STDLIB_H_

#include_next <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void abort(void);

void exit(int status);

#ifdef __cplusplus
}
#endif

#endif // not _SIM_STDLIB_H_
