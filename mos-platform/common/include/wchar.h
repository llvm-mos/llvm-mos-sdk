// Stub implementation of wchar.h.

#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long mbstate_t;
typedef unsigned long wint_t;

#define WEOF 0xFFFFFFFFul

#ifdef __cplusplus
}
#endif

#endif // not _WCHAR_H_
