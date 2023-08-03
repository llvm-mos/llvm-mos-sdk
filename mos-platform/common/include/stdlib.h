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

void exit(int status);
__attribute__((leaf)) void abort(void);
__attribute__((leaf)) void _exit(int status);
__attribute__((leaf)) void _Exit(int status);

int atexit(void (*function)(void));

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

// clang-format off
/**
Simple malloc/free implementation.

Note: if your program does not need to use the heap, then do not call
any of these functions. The entire heap implementation is only allocated
in your program if you actually call the allocation functions.

Currently the heap is implemented using a first-fit free list. The heap
segment is placed directly after BSS in your program.  The heap can
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

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t size);

/* The maximum heap size can be limited in the following ways:
1. If no heap allocation has been made yet, the heap limit can be set to any
   size greater than the implementation-defined minimum block size. This actual
   minimum is only a few bytes, but for practical purposes if you are using the
   heap, you should at least plan on using 100's or 1000's of bytes.
2. If an allocation is made prior to setting the heap limit, the initial limit
   is set to an implementation-defined default. The actual limit may depend
   on the available address space of the target platform.
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
   function if you aren't going to use the heap. */
void __set_heap_limit(size_t new_size);

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

#ifdef __cplusplus
}
#endif

#endif // not _STDLIB_H_
