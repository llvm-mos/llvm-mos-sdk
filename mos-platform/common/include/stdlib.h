#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>

#ifndef __LLVM_MOS_SDK
#define __LLVM_MOS_SDK 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 32767

#define MB_CUR_MAX ((size_t)1)

int abs(int i);
long labs(long i);
long long llabs(long long i);

int atoi(const char *s);
long atol(const char *s);

typedef struct {
  int quot;
  int rem;
} div_t;
div_t div(int numer, int denom);

typedef struct {
  long quot;
  long rem;
} ldiv_t;
ldiv_t ldiv(long numer, long denom);

typedef struct {
  long long quot;
  long long rem;
} lldiv_t;
lldiv_t lldiv(long long numer, long long denom);

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);

long strtol(const char *__restrict__ nptr, char **__restrict endptr, int base);
long long strtoll(const char *__restrict__ nptr, char **__restrict endptr,
                  int base);
unsigned long strtoul(const char *__restrict__ nptr, char **__restrict endptr,
                      int base);
unsigned long long strtoull(const char *__restrict__ nptr,
                            char **__restrict endptr, int base);

// Non-standard strtox functions for smaller types.
signed char _strtosc(const char *__restrict__ nptr, char **__restrict endptr,
                     int base);
unsigned char _strtouc(const char *__restrict__ nptr, char **__restrict endptr,
                       int base);
int _strtoi(const char *__restrict__ nptr, char **__restrict endptr, int base);
unsigned int _strtoui(const char *__restrict__ nptr, char **__restrict endptr,
                      int base);

int rand(void);
void srand(unsigned seed);

// clang-format off
/**
Simple malloc/free implementation.

Note: if your program does not need to use the heap, then do not call
any of these functions. The entire heap implementation is only allocated
in your program if you actually call the allocation functions.

The heap segment is placed directly after BSS in your program. The heap can
utilize any of the memory between the base heap address and the top of the
software-defined stack.

Typical memory map, for a target that loads programs into RAM:

                                         ┌─────────────────────────────────┐
                                         │Reserved or otherwise unavailable│
0xFFFF┌────────────────────────────┐  ┌──│     memory. Ex: ROM or I/O      │
      │                            │◀─┘  └─────────────────────────────────┘
      │                            │
      ├────────────────────────────┤◀┐
      │               │            │ │  ┌───────────────────────────────────────┐
      │     Stack     │            │ │  │Stack base.  As stack usage grows, more│
      │               │            │ └──│memory below this address is utilized. │
      │               ▼            │    └───────────────────────────────────────┘
      │                            │
      ├ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─│◀─┐  ┌────────────────────────────────────────┐
      │                            │  │  │Actual lower limit for stack depends on │
      │                            │  │  │how much stack space your code actually │
      │                            │  └──│needs.  Generally it can't be determined│
      │                            │     │             ahead of time.             │
      │                            │     └────────────────────────────────────────┘
      ├ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─│◀┐
      │                            │ │
      │                            │ │
      │                            │ │
      │                            │ │  ┌───────────────────────────────────────┐
      │                            │ │  │Heap limit.  You can set this from     │
      │            ▲               │ └──│within your program.                   │
      │     Heap   │               │    └───────────────────────────────────────┘
      │            │               │
      ├────────────────────────────┤◀┐
      │                            │ │  ┌───────────────────────────────────────┐
      │   Your program is loaded   │ │  │   Heap base pointer.  It's location   │
      │           here.            │ │  │depends on how big your program is and │
      │                            │ └──│how much memory it allocated in global │
      ├────────────────────────────┤    │         and static variables.         │
      │                            │    └───────────────────────────────────────┘
      │   Reserved lower memory:   │
      │         zero-page,         │
      │    hardware stack, etc.    │
      │                            │
      │                            │
0x0000└────────────────────────────┘
*/
// clang-format on

void *aligned_alloc(size_t alignment, size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

/* The maximum heap size can be limited in the following ways:
1. If no heap allocation has been made yet, the heap limit can be set to any
   size greater than the implementation-defined minimum block size. This actual
   minimum is only a few bytes, but for practical purposes if you are using the
   heap, you should at least plan on using 100's or 1000's of bytes.
2. If an allocation is made prior to setting the heap limit, the initial limit
   is set to the value of the symbol `__heap_default_limit`. The actual limit
   may depend on the available address space of the target platform.
3. After the first allocation has been made, the heap may only increase in size.
   Any attempt to decrease the size of the heap limit will be ignored.

Increasing the heap limit does not do any validation to ensure the heap will not
collide with the stack. You must leave enough space for whatever stack usage
your program needs.
*/

/* Return the current maximium size of the heap. */
size_t __heap_limit();

/* Set the maximum size of the heap.  Note the limitations above. */
/* Setting the heap limit implicitly allocates the heap.  Don't call this
 * function if you aren't going to use the heap.  Returns the value actually
 * set -- this value is capped to avoid trashing the stack. 
 */
size_t __set_heap_limit(size_t limit);

/* Return the maximum safe heap size to avoid stack collision. */
size_t __get_heap_max_safe_size(void);

/* Return heap bytes in use, including overhead for heap data structures in
   the existing allocations. */
size_t __heap_bytes_used();

/* Return heap bytes available for future allocations.  This does not take into
   account the overhead of the heap itself, which depends on how many
   allocations are made.*/
size_t __heap_bytes_free();

#ifdef _MOS_SOURCE

#define heap_limit __heap_limit
#define set_heap_limit __set_heap_limit
#define heap_bytes_used __heap_bytes_used
#define heap_bytes_free __heap_bytes_free

#endif // _MOS_SOURCE

// Communication with the environment

_Noreturn void abort(void);
int atexit(void (*func)(void));
int at_quick_exit(void (*func)(void));
_Noreturn void exit(int status);
__attribute__((leaf)) _Noreturn void _Exit(int status);
char *getenv(const char *name);
_Noreturn void quick_exit(int status);
int system(const char *string);

// Sorting and searching utilities

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif // not _STDLIB_H_
