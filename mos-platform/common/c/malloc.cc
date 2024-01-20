#include <stdlib.h>

#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MALLOC_TRACE 0

#define TRACE(fmt, ...)                                                        \
  if (MALLOC_TRACE)                                                            \
  printf(fmt __VA_OPT__(, ) __VA_ARGS__)

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

  // Returns the previous free chunk or nullptr.
  FreeChunk *prev_free_chunk() const;
  Chunk *next() const;

  // Slow; prefer prev_free where possible.
  bool free() const;
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

void *heap_end() { return &__heap_start + heap_limit; }

// The sum total available size on the free list.
size_t free_size;

// A circularly-linked list of free chunks ordered by decreasing age. NULL if
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

FreeChunk *Chunk::prev_free_chunk() const {
  if (!prev_free)
    return NULL;

  size_t prev_size = *reinterpret_cast<size_t *>((char *)this - sizeof(size_t));
  return reinterpret_cast<FreeChunk *>((char *)this - prev_size);
}

bool Chunk::free() const {
  Chunk *n = next();
  return n ? n->prev_free : last_free;
}

// Remove a free chunk from the free list.
void FreeChunk::remove() {
  TRACE("FreeChunk(%p)::remove\n", this);

  free_size -= avail_size();

  if (free_list_next == this) {
    TRACE("Free list emptied.\n");
    free_list = NULL;
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
// of the given size and alignment. If alignment is not 2, offset is set to the
// offset of the new chunk that would cause the point after the header to be at
// the correct alignment.
FreeChunk *find_fit(size_t size, size_t alignment, size_t *offset) {
  TRACE("find_fit(%u, %u)\n", size, alignment);

  if (!free_list) {
    TRACE("Free list empty.\n");
    return NULL;
  }

  bool first = true;
  for (FreeChunk *chunk = free_list; first || chunk != free_list;
       chunk = chunk->free_list_next, first = false) {
    TRACE("Considering free chunk @ %p size %u\n", chunk, chunk->size());

    if (size > chunk->size())
      continue;

    if (alignment == 2) {
      TRACE("Selected.\n");
      return chunk;
    }

    // Offsets must always leave room for a free chunk; otherwise there's no way
    // to track the space.
    *offset = MIN_CHUNK_SIZE;

    // Align the point immediately after the chunk header. Since the alignment
    // is guaranteed to be a multiple of two, this also leaves the chunk start
    // aligned to two.
    uintptr_t offset_point;
    if (__builtin_add_overflow((uintptr_t)chunk, *offset + sizeof(Chunk),
                               &offset_point))
      continue;

    // Alignment is always a power of two.
    size_t misaligned_bits_mask = alignment - 1;

    size_t offset_past_alignment = offset_point & misaligned_bits_mask;
    if (offset_past_alignment) {
      // Move backwards to the nearest aligned point.
      *offset &= ~misaligned_bits_mask;
      // Move forwards by the alignment.
      if (__builtin_add_overflow(*offset, alignment, offset))
        continue;
    }

    TRACE("Offset: %u\n", *offset);

    // if (*offset + size <= chunk->size()) (may overflow)
    if (*offset <= chunk->size() - size) {
      TRACE("Selected.\n");
      return chunk;
    }
  }

  TRACE("None found.\n");
  return NULL;
}

// Allocate at chunk of size bytes from a free chunk such that the new chunk
// begins at the given offset. The pointer returned points after the chunk
// header.
void *allocate_free_chunk(FreeChunk *free_chunk, size_t size, size_t offset) {
  TRACE("allocate_free_chunk(%p,%u,%u)\n", free_chunk, size, offset);
  free_chunk->remove();

  // From this point on the chunk is no longer free.
  Chunk *chunk = free_chunk;

  if (offset) {
    TRACE("Inserting aligned offset free chunk.\n");

    // Offset is guaranteed to be large enough for a free chunk. prev_free
    // retains its value from chunk.
    FreeChunk::insert(chunk, offset);

    // Advance the chunk pointer forward and establish a new one.
    size_t csize = chunk->size();
    chunk = (Chunk *)((char *)chunk + offset);
    chunk->set_size(csize - offset);
    chunk->prev_free = true;
    TRACE("Advanced chunk to %p, remaining size %u\n", chunk, chunk->size());
  }

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

  Chunk *next = chunk->next();
  if (next)
    next->prev_free = false;
  else
    last_free = false;

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
    FreeChunk *last = free_list->free_list_prev;
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

__attribute__((weak)) void *aligned_alloc(size_t alignment, size_t size) {
  TRACE("aligned_alloc(%u,%u)\n", alignment, size);

  if (alignment <= 2)
    return malloc(size);

  if (!size)
    return NULL;

  // Only power of two alignments are valid.
  if (alignment & (alignment - 1))
    return NULL;

  if (!initialized)
    init();

  if (__builtin_add_overflow(size, sizeof(Chunk), &size))
    return NULL;
  TRACE("Increased size to %u to account for chunk header.\n", size);

  if (size < MIN_CHUNK_SIZE) {
    size = MIN_CHUNK_SIZE;
    TRACE("Increased size to minimum chunk size %u\n", size);
  } else if (size & 1) {
    if (__builtin_add_overflow(size, 1, &size))
      return NULL;
    TRACE("Increased size to %u to ensure sizes aligned to 2.\n", size);
  }

  size_t offset;
  FreeChunk *chunk = find_fit(size, alignment, &offset);
  if (!chunk)
    return NULL;

  return allocate_free_chunk(chunk, size, offset);
}

__attribute__((weak)) void free(void *ptr) {
  TRACE("free(%p)\n", ptr);
  if (!ptr)
    return;

  Chunk *chunk = (Chunk *)((char *)ptr - sizeof(Chunk));
  size_t size = chunk->size();

  TRACE("Freeing chunk %p of size %u\n", chunk, size);

  // Coalesce with prev and next if possible, replacing chunk.
  FreeChunk *prev = chunk->prev_free_chunk();
  Chunk *next = chunk->next();

  if (prev) {
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

__attribute__((weak)) void *malloc(size_t size) {
  if (!size)
    return NULL;

  TRACE("malloc(%u)\n", size);

  if (!initialized)
    init();

  if (__builtin_add_overflow(size, sizeof(Chunk), &size))
    return NULL;
  TRACE("Increased size to %u to account for chunk header.\n", size);

  if (size < MIN_CHUNK_SIZE) {
    size = MIN_CHUNK_SIZE;
    TRACE("Increased size to minimum chunk size %u\n", size);
  } else if (size & 1) {
    if (__builtin_add_overflow(size, 1, &size))
      return NULL;
    TRACE("Increased size to %u to ensure sizes aligned to 2.\n", size);
  }

  FreeChunk *chunk = find_fit(size, /*alignment=*/2, /*offset=*/NULL);
  if (!chunk)
    return NULL;

  return allocate_free_chunk(chunk, size, /*offset=*/0);
}

__attribute__((weak)) void *realloc(void *ptr, size_t size) {
  TRACE("realloc(%p, %u)\n", ptr, size);

  if (!size)
    return NULL;
  if (!ptr)
    return malloc(size);

  // Keep original size around for malloc fallback.
  size_t malloc_size = size;

  if (__builtin_add_overflow(size, sizeof(Chunk), &size))
    return NULL;
  TRACE("Increased size to %u to account for chunk header.\n", size);

  if (size < MIN_CHUNK_SIZE) {
    size = MIN_CHUNK_SIZE;
    TRACE("Increased size to minimum chunk size %u\n", size);
  } else if (size & 1) {
    if (__builtin_add_overflow(size, 1, &size))
      return NULL;
    TRACE("Increased size to %u to ensure sizes aligned to 2.\n", size);
  }

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
    Chunk *after_next = after->next();
    if (after_next)
      after_next->prev_free = true;
    else
      last_free = true;
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

      return ptr;
    }
  }

  TRACE("Reallocating by copy.\n");
  void *new_ptr = malloc(malloc_size);
  if (!new_ptr)
    return NULL;
  memcpy(new_ptr, ptr, old_size);
  free(ptr);
  return new_ptr;
}

} // extern "C"
