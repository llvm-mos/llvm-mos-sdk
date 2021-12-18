#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void abort(void);
void exit(int status);

int abs(int i);
long labs(long i);
long long llabs(long long i);

void *malloc(size_t size);
void free(void * ptr);
void *calloc(size_t num, size_t size);

void abort();

#ifdef __cplusplus
}
#endif

#endif // not _STDLIB_H_
