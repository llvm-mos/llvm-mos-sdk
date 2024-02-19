#include <stdlib.h>

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef NDEBUG
#define TRACE(fmt, ...)                                                        \
  printf(fmt __VA_OPT__(, ) __VA_ARGS__)
#else
#define TRACE(fmt, ...) (void)0
#endif

extern char __heap_start;
extern char __heap_default_limit;

namespace {

class FreeChunk;

class Chunk {
public:
  char prev_free : 1;

private:
  size_t size_hi : 15;

public:
  size_t size() const { return size_hi << 1; }
  void set_size(size_t size) { size_hi = size >> 1; }

  void *end() const { return (char *)this + size(); }

  // Returns the previous chunk. Undefined behavior if the previous chunk is not
  // free. Legal to call on a pointer to heap end.
  FreeChunk *prev() const;

  Chunk *next() const;

  // Slow; prefer prev_free where possible.
  bool free() const;

  void set_free(bool free);
};

class FreeChunk : public Chunk {
public:
  struct FreeChunk *free_list_next;
  struct FreeChunk *free_list_prev;
  // char filler[...];
  // size_t trailing_size;

  // Initialize a region of memory as a free chunk, add it to the free list, and
  // return it.
  static FreeChunk *insert(void *begin, size_t size);

  size_t &trailing_size() {
    return *(size_t *)((char *)end() - sizeof(size_t));
  }

  size_t avail_size() const { return size() - sizeof(Chunk); }

  // Remove from the free list.
  void remove();
};

// Free chunks smaller than this cannot be allocated, and in-use chunks smaller
// than this cannot be freed if surrounded by in-use chunks. Accordingly, this
// acts as a global minimum chunk size.
constexpr size_t MIN_CHUNK_SIZE = sizeof(FreeChunk) + sizeof(size_t);

size_t heap_limit = (size_t)&__heap_default_limit;

Chunk *heap_end() {
  return reinterpret_cast<Chunk *>(&__heap_start + heap_limit);
}

// The sum total available size on the free list.
size_t free_size;

// A circularly-linked list of free chunks ordered by decreasing age. nullptr if
// empty.
FreeChunk *free_list;

// Free-ness is tracked by the next chunk's prev_free field, but the last chunk
// has no next chunk.
bool last_free;

bool initialized;

Chunk *Chunk::next() const {
  Chunk *next = reinterpret_cast<Chunk *>(end());
  return next != heap_end() ? next : nullptr;
}

FreeChunk *Chunk::prev() const {
  size_t prev_size = *reinterpret_cast<size_t *>((char *)this - sizeof(size_t));
  return reinterpret_cast<FreeChunk *>((char *)this - prev_size);
}

bool Chunk::free() const {
  Chunk *n = next();
  return n ? n->prev_free : last_free;
}

void Chunk::set_free(bool free) {
  Chunk *n = next();
  if (n)
    n->prev_free = free;
  else
    last_free = free;
}

// Remove a free chunk from the free list.
void FreeChunk::remove() {
  TRACE("FreeChunk(%p)::remove\n", this);

  free_size -= avail_size();

  if (free_list_next == this) {
    TRACE("Free list emptied.\n");
    free_list = nullptr;
    return;
  }

  free_list_prev->free_list_next = free_list_next;
  free_list_next->free_list_prev = free_list_prev;
  if (free_list == this)
    free_list = free_list_next;
}

// Initialize a region of memory as a free chunk and add it to the free list.
FreeChunk *FreeChunk::insert(void *begin, size_t size) {
  TRACE("FreeChunk::insert(%p, %u)\n", begin, size);
  FreeChunk *chunk = (FreeChunk *)begin;
  chunk->set_size(size);
  chunk->trailing_size() = size;
  free_size += chunk->avail_size();

  if (!free_list) {
    free_list = chunk->free_list_next = chunk->free_list_prev = chunk;
    return chunk;
  }

  // Insert to the end of the free list, so that allocations from the front
  // occur in FIFO order (first fit FIFO in Wilson et al).
  chunk->free_list_next = free_list;
  chunk->free_list_prev = free_list->free_list_prev;
  chunk->free_list_prev->free_list_next = chunk;
  chunk->free_list_next->free_list_prev = chunk;
  return chunk;
}

// Find the first chunk in the free list that can successfully fit a new chunk
// of the given size.
FreeChunk *find_fit(size_t size) {
  TRACE("find_fit(%u)\n", size);

  if (!free_list) {
    TRACE("Free list empty.\n");
    return nullptr;
  }

  bool first = true;
  for (FreeChunk *chunk = free_list; first || chunk != free_list;
       chunk = chunk->free_list_next, first = false) {
    TRACE("Considering free chunk @ %p size %u\n", chunk, chunk->size());

    if (size <= chunk->size()) {
      TRACE("Selected.\n");
      return chunk;
    }
  }

  TRACE("None found.\n");
  return nullptr;
}

// Allocate at chunk of size bytes from a free chunk. The pointer returned
// points to the contents (past the chunk header).
void *allocate_free_chunk(FreeChunk *free_chunk, size_t size) {
  TRACE("allocate_free_chunk(%p,%u)\n", free_chunk, size);
  free_chunk->remove();

  // From this point on the chunk is no longer free.
  Chunk *chunk = free_chunk;

  size_t remainder = chunk->size() - size;
  if (remainder < MIN_CHUNK_SIZE) {
    TRACE("Remainder %u too small; allocating whole chunk\n", remainder);
  } else {
    TRACE("Inserting remainder chunk\n");
    // The prev_free (or last_free) referencing the current chunk is guaranteed
    // true, and it can remain true now that it refers to the remainder.
    FreeChunk::insert((char *)chunk + size, remainder);
    chunk->set_size(size);
  }

  chunk->set_free(false);

  TRACE("Allocated size: %u\n", size);

  char *ptr = (char *)chunk + sizeof(Chunk);
  TRACE("Allocated ptr: %p\n", ptr);
  return ptr;
}

void init() {
  TRACE("Initialized heap. Start: %p Limit: %u\n", &__heap_start, heap_limit);
  FreeChunk::insert(&__heap_start, heap_limit)->prev_free = false;
  last_free = true;
  initialized = true;
}

} // namespace

extern "C" {

size_t __heap_limit() { return heap_limit; }

void __set_heap_limit(size_t new_limit) {
  TRACE("__set_heap_limit(%u)\n", new_limit);

  // Chunk sizes must be a multiple of two.
  if (new_limit & 1)
    --new_limit;

  if (!initialized) {
    heap_limit = (new_limit < MIN_CHUNK_SIZE) ? MIN_CHUNK_SIZE : new_limit;
    TRACE("Heap not yet initialized. Set limit to %u.\n", heap_limit);
    return;
  }

  // TODO: We can make this actually shrink the heap too...
  if (new_limit <= heap_limit) {
    TRACE("New limit %u smaller than current %u; returning.", new_limit,
          heap_limit);
    return;
  }

  size_t grow = new_limit - heap_limit;
  TRACE("Growing heap by %u\n", grow);
  if (last_free) {
    FreeChunk *last = heap_end()->prev();
    TRACE("Last chunk free; size %u\n", last->size());
    size_t new_size = last->size() + grow;
    last->set_size(new_size);
    last->trailing_size() = new_size;
    TRACE("Expanded to %u\n", new_size);
    free_size += grow;
  } else {
    TRACE("Last chunk not free.\n");
    if (grow < MIN_CHUNK_SIZE) {
      TRACE("Not enough new size for a chunk; returning.\n");
      return;
    }
    TRACE("Inserting new chunk.\n");
    FreeChunk::insert(heap_end(), grow);
    last_free = true;
  }

  heap_limit = new_limit;
}

size_t __heap_bytes_used() { return heap_limit - free_size; }

size_t __heap_bytes_free() { return free_size; }

// Return the size of chunk needed to hold a malloc request, or zero if
// impossible.
size_t chunk_size_for_malloc(size_t size) {
  if (size <= MIN_CHUNK_SIZE - sizeof(Chunk)) {
    TRACE("Increased size to minimum chunk size %u\n", MIN_CHUNK_SIZE);
    return MIN_CHUNK_SIZE;
  }

  char overhead = sizeof(Chunk);
  if (size & 1)
    overhead++;

  if (__builtin_add_overflow(size, overhead, &size))
    return 0;
  TRACE("Increased size to %u to account for overhead.\n", size);
  return size;
}

void *aligned_alloc(size_t alignment, size_t size) {
  TRACE("aligned_alloc(%u,%u)\n", alignment, size);

  if (alignment <= 2)
    return malloc(size);

  if (!size)
    return nullptr;

  // Only power of two alignments are valid.
  if (alignment & (alignment - 1))
    return nullptr;

  size = chunk_size_for_malloc(size);
  if (!size)
    return nullptr;

  // The region before the aligned chunk needs to be large enough to fit a freereallocated chunk should not be free");
  // chunk.
  if (__builtin_add_overflow(size, MIN_CHUNK_SIZE, &size))
    return nullptr;

  // Up to alignment-1 additional bytes may be needed to align the chunk start.
  if (__builtin_add_overflow(size, alignment - 1, &size))
    return nullptr;

  if (!initialized)
    init();

  FreeChunk *chunk = find_fit(size);
  if (!chunk)
    return nullptr;

  void *aligned_ptr = (char *)chunk + MIN_CHUNK_SIZE;
  TRACE("Initial alignment point: %p\n", aligned_ptr);

  // alignment is a power of two, so alignment-1 is a mask that selects the
  // misaligned bits.
  size_t past_alignment = (uintptr_t)aligned_ptr & (alignment - 1);
  if (past_alignment) {
    TRACE("%u bytes past aligned point.\n", past_alignment);
    aligned_ptr = (void *)((uintptr_t)aligned_ptr & ~(alignment - 1));
    TRACE("Moved pointer backwards to aligned point %p.\n", aligned_ptr);
    aligned_ptr = (char *)aligned_ptr + alignment;
    TRACE("Moved pointer one alignment unit forwards to %p.\n", aligned_ptr);
  }

  size_t chunk_size = chunk->size();

  auto *aligned_chunk_begin = (Chunk *)((char *)aligned_ptr - sizeof(Chunk));
  size_t prev_chunk_size = (char *)aligned_chunk_begin - (char *)chunk;

  TRACE("Inserting free chunk before aligned.\n");
  FreeChunk::insert(chunk, prev_chunk_size); // prev_free remains unchanged.

  TRACE("Temporarily inserting aligned free chunk.\n");
  FreeChunk *aligned_chunk =
      FreeChunk::insert(aligned_chunk_begin, chunk_size - prev_chunk_size);
  aligned_chunk->prev_free = true;

  TRACE("Allocating from aligned free chunk.\n");
  return allocate_free_chunk(aligned_chunk, size);
}

void *calloc(size_t num, size_t size) {
  const auto long_sz = (long)num * size;
  if (long_sz >> 16)
    return 0;
  const auto sz = (size_t)long_sz;
  const auto block = malloc(sz);

  if (!block)
    return nullptr;

  __memset(static_cast<char *>(block), 0, sz);
  return block;
}

void free(void *ptr) {
  TRACE("free(%p)\n", ptr);
  if (!ptr)
    return;

  Chunk *chunk = (Chunk *)((char *)ptr - sizeof(Chunk));
  size_t size = chunk->size();

  TRACE("Freeing chunk %p of size %u\n", chunk, size);

  // Coalesce with prev and next if possible, replacing chunk.
  Chunk *next = chunk->next();
  if (chunk->prev_free) {
    FreeChunk *prev = chunk->prev();
    size_t prev_size = prev->size();
    TRACE("Coalescing with previous free chunk %p of size %u\n", prev,
          prev_size);
    prev->remove();
    size += prev_size;
    chunk = prev;
    TRACE("New chunk %p of size %u\n", chunk, size);
  }
  if (next) {
    size_t next_size = next->size();
    TRACE("Next chunk: %p size %u\n", next, next_size);
    if (next->free()) {
      TRACE("Coalescing with next free chunk %p of size %u\n", next, next_size);
      static_cast<FreeChunk *>(next)->remove();
      size += next_size;
      TRACE("New chunk size %u\n", size);
    } else {
      TRACE("Next chunk not free.\n");
      next->prev_free = true;
    }
  } else {
    TRACE("No next chunk; last chunk now free.\n");
    last_free = true;
  }

  FreeChunk::insert(chunk, size);
}

void *malloc(size_t size) {
  if (!size)
    return nullptr;

  TRACE("malloc(%u)\n", size);

  size = chunk_size_for_malloc(size);
  if (!size)
    return nullptr;

  if (!initialized)
    init();

  FreeChunk *chunk = find_fit(size);
  if (!chunk)
    return nullptr;

  return allocate_free_chunk(chunk, size);
}

void *realloc(void *ptr, size_t size) {
  TRACE("realloc(%p, %u)\n", ptr, size);

  if (!size)
    return nullptr;
  if (!ptr)
    return malloc(size);

  // Keep original size around for malloc fallback.
  size_t malloc_size = size;

  size = chunk_size_for_malloc(size);
  if (!size)
    return nullptr;

  Chunk *chunk = (Chunk *)((char *)ptr - sizeof(Chunk));
  size_t old_size = chunk->size();
  TRACE("Old size: %u\n", old_size);

  if (size < old_size) {
    size_t shrink = size - old_size;
    TRACE("Shrinking by %u\n", shrink);
    Chunk *next = chunk->next();
    chunk->set_size(size);

    if (next && next->free()) {
      size_t next_size = next->size();
      TRACE("Next free chunk %p size %u\n", next, next_size);
      // Coalesce.
      static_cast<FreeChunk *>(next)->remove();
      FreeChunk::insert(chunk->end(), shrink + next_size)->prev_free = false;
      return ptr;
    }

    // Insert a new free chunk for the shrink if possible.
    if (shrink < MIN_CHUNK_SIZE) {
      TRACE("Remainder too small.");
      return ptr;
    }

    FreeChunk *after = FreeChunk::insert(chunk->end(), shrink);
    TRACE("Allocated remainder %p of size %u\n", after, after->size());
    after->prev_free = false;
    after->set_free(true);
    return ptr;
  }

  if (size == old_size) {
    TRACE("Destination size the same as current; done.\n");
    return ptr;
  }

  size_t grow = size - old_size;
  TRACE("Growing by %u\n", grow);
  Chunk *next = chunk->next();
  if (next) {
    size_t next_size = next->size();
    if (next->free() && grow <= next_size) {
      TRACE("Stealing from next chunk %p free w/ size %u\n", next, next_size);
      chunk->set_size(size);
      static_cast<FreeChunk *>(next)->remove();

      if (next_size - grow < MIN_CHUNK_SIZE) {
        chunk->set_size(old_size + next_size);
        TRACE("Not enough remainder, so size now %u\n", chunk->size());
      } else {
        TRACE("Inserting remainder of next chunk.\n");
        FreeChunk::insert(chunk->end(), next_size - grow)->prev_free = false;
      }

      assert(!chunk->free() && "newly reallocated chunk should not be free");
      return ptr;
    }
  }

  TRACE("Reallocating by copy.\n");
  void *new_ptr = malloc(malloc_size);
  if (!new_ptr)
    return nullptr;
  memcpy(new_ptr, ptr, old_size);
  free(ptr);
  return new_ptr;
}

} // extern "C"
