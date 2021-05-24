
#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void *dest, const void *src, size_t count);

void* memset(void *ptr, int value, size_t num);

#ifdef __cplusplus
}
#endif

#endif // not _STRING_H_
