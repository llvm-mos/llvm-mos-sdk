#include <cstdint>
#include <new>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern std::byte __heap_start;

namespace {

// An arbitrary block of memory. This struct only holds the size of the block,
// and the data in the block directly follows.
struct block {
  block(std::size_t size) : m_size{size} {}

  static block *get_block(std::byte *data) {
    return reinterpret_cast<block *>(data - sizeof(m_size));
  }

  std::size_t m_size;

  std::byte *data() { return static_cast<std::byte *>(m_data); }

  std::byte m_data[];
};

static_assert(sizeof(block) == sizeof(std::size_t), "!!!");


// This is a first fit free list allocator.
// It is initialized with a single element; and only increases in size if the heap
// becomes fragmented.  So; even though it's operations are linear with respect
// to the number of "holes" made in the heap through fragmentation.

// This allocator is suitable for 8-bit systems with 16-bit, 64kbyte address spaces.  In that
// scenario the worst case scenario would be the maximum amount of allcations where each allocation
// is the smallest allocation, which is 2 bytes.
// The maximum number of allocations is 64kbyte / 8 bytes = 8 k allocs:
//   6 bytes per block + 2 byte minimum allocation.
// In order to have holes, each allocation would have to be separated from an adjacent
// allocation by some free memory.  So the maximum number of holes is half the maximum
// number of allocs: 8k / 2 = 4k.
// In that scenario; randomly freeing or allocing, there would be, at most, 4096 entries to traverse.


// A doubly-linked list of blocks of memory.
// The next node pointer, the previous node pointer, and the size of the block
// are stored at the beginning of the block.
class blocklist {
  // pointers to next and previous.
  struct list_node {
    list_node *m_next = nullptr;
    list_node *m_prev = nullptr;
  };

  // The entire block node pointer, which is embedded in the block itself.
  struct block_node : public list_node {
    block_node(std::size_t initsz) : m_block{initsz - sizeof(block_node)} {}

    block m_block;

    static block_node *get_node(block &blk) {
      return reinterpret_cast<block_node *>(
          reinterpret_cast<std::byte *>(&blk) - sizeof(list_node));
    }
  };

public:
  static constexpr std::uint8_t MIN_ALLOC_SIZE = sizeof(block_node) + 2;

  blocklist() {
    m_heap_limit = m_heap_limit == SIZE_MAX ? HEAP_DEFAULT_LIMIT : m_heap_limit;
    m_head = new (&__heap_start) block_node{m_heap_limit};
    m_used = sizeof(block_node);
    m_free = m_head->m_block.m_size;
  }

  struct iterator {
  public:
    iterator() = default;
    iterator(block_node *ptr) : m_ptr{ptr} {}

    block &operator*() const { return m_ptr->m_block; }

    iterator &operator++() {
      m_ptr = static_cast<block_node *>(m_ptr->m_next);
      return *this;
    }

    bool operator==(const iterator &rhs) const {
      return m_ptr == rhs.m_ptr;
    }

    bool operator!=(const iterator &rhs) const {
      return !this->operator==(rhs);
    }

  private:
    block_node *m_ptr = nullptr;
  };

  iterator begin() { return m_head; }

  iterator end() { return iterator{}; }

  static_assert(sizeof(list_node) ==
                    sizeof(list_node::m_next) + sizeof(list_node::m_prev),
                "unexpected padding");
  static_assert(sizeof(block_node) == sizeof(list_node) + sizeof(std::size_t),
                "unexpected padding");

  std::byte *split_block(block *freeblock, std::size_t size) {
    if (!freeblock) {
      return nullptr;
    }

    if ((freeblock->m_size - size) >= blocklist::MIN_ALLOC_SIZE) {
      const auto new_blk =
          new (freeblock->data() + size) block_node{freeblock->m_size - size};
      freeblock->m_size = size;

      const auto freeblock_node_ptr = block_node::get_node(*freeblock);
      {
        const auto next_block_ptr = new_blk->m_next =
            freeblock_node_ptr->m_next;
        if (next_block_ptr) {
          next_block_ptr->m_prev = new_blk;
        }
      }

      const auto prev_block_ptr = new_blk->m_prev = freeblock_node_ptr->m_prev;
      if (prev_block_ptr) {
        prev_block_ptr->m_next = new_blk;
      } else {
        m_head = new_blk;
      }

      // A new node in free list was allocated. Remove it from the total bytes
      // free.
      m_used += sizeof(block_node);
      m_free -= sizeof(block_node);
    } else {
      // Drop the block from the free list entirely.
      const auto freeblock_node_ptr = block_node::get_node(*freeblock);
      const auto prev_block_ptr = freeblock_node_ptr->m_prev;
      const auto next_block_ptr = freeblock_node_ptr->m_next;

      if (prev_block_ptr) {
        prev_block_ptr->m_next = next_block_ptr;
      } else {
        m_head = static_cast<block_node *>(next_block_ptr);
      }

      if (next_block_ptr) {
        next_block_ptr->m_prev = prev_block_ptr;
      }
    }

    // Update stats for actual size allocated.
    m_used += freeblock->m_size;
    m_free -= freeblock->m_size;
    return freeblock->data();
  }

  // Traverse the free block list to find the first one big enough to handle
  // the requested allocation.  This is O(n) terms of free blocks.
  block *find_first_fit(std::size_t sz) {
    for (auto &block : *this) {
      if (block.m_size >= (sz + sizeof(block_node))) {
        return &block;
      }
    }

    return nullptr;
  }

  // Traverse the free block list to find the free block after the given block.
  // If the block is
  // 1. directly following the given block
  // 2. large enough to hold the given size request
  // then the the block is returned.
  block *find_adjacent_fit(block *base_blk_ptr, std::size_t sz) {

    const auto adjacent_ptr =
        static_cast<void *>(base_blk_ptr->data() + base_blk_ptr->m_size);

    for (auto &free_blk : *this) {
      const auto free_node_ptr = block_node::get_node(free_blk);
      if (block_node::get_node(free_blk) == adjacent_ptr) {
        // Adjacent block is free.
        // See if there is enough space free to realloc. We do not need
        // to account for creating another block, since the free_blk m_size
        // member already excludes the bytes for the free block node, and that block
        // node will just get moved further into the free block.
        if (free_blk.m_size >= sz) {
          // Adjacent block is free and large enough.
          return &free_blk;
        } else {
          // Adjacent block is not large enough.
          return nullptr;
        }
      } else if (&free_blk > adjacent_ptr) {
        // Adjacent block not found in free list.  Early exit.
        return nullptr;
      }
      // Continue to next block.
    }
    return nullptr;
  }

  // Free a block by re-inserting it in the free list.
  // Freeing blocks is O(n) in terms of number of free segments that have to be traversed
  // to find the place in the free list to restore the block.  In cases of low fragmentation,
  // the size of this list will be low.
  void free_block(block *const block) {
    block_node *last_block_node = nullptr;
    for (auto &free_blk : *this) {
      if (&free_blk > block) {
        const auto freed_block_ptr = block_node::get_node(*block);
        const auto next_block_ptr = block_node::get_node(free_blk);
        const auto prev_block_ptr = next_block_ptr->m_prev;

        freed_block_ptr->m_next = next_block_ptr;
        next_block_ptr->m_prev = freed_block_ptr;
        freed_block_ptr->m_prev = prev_block_ptr;

        if (prev_block_ptr) {
          prev_block_ptr->m_next = freed_block_ptr;
        } else {
          m_head = freed_block_ptr;
        }

        m_free += block->m_size;
        m_used -= block->m_size;
        return;
      }

      last_block_node = block_node::get_node(free_blk);
    }

    const auto freed_block_ptr = block_node::get_node(*block);
    last_block_node->m_next = freed_block_ptr;
    freed_block_ptr->m_prev = last_block_node;
    freed_block_ptr->m_next = nullptr;
    m_free += block->m_size;
    m_used -= block->m_size;
  }

  // Run a linear scan through the free list to find adjacent free blocks,
  // and join adjacent blocks.  This is linear in terms of the number of
  // blocks. Coallescing is run after every free_block operation in order
  // to keep the size of the free list small.
  void coalesce_blocks() {
    block *last_block = nullptr;

    for (auto &block : *this) {
      if (last_block) {
        const auto block_node_ptr = block_node::get_node(block);
        if (static_cast<void *>(last_block->data() + last_block->m_size) ==
            static_cast<void *>(block_node_ptr)) {
          // two free sequential blocks.
          last_block->m_size += sizeof(*block_node_ptr) + block.m_size;
          const auto last_block_node = block_node::get_node(*last_block);
          last_block_node->m_next = block_node_ptr->m_next;
          if (last_block_node->m_next) {
            last_block_node->m_next->m_prev = last_block_node;
          }
          m_used -= sizeof(block_node);
          m_free += sizeof(block_node);
          continue;
        }
      }

      last_block = &block;
    }
  }

  void set_new_limit(std::size_t new_limit) {
    if (new_limit >= (m_heap_limit + MIN_ALLOC_SIZE)) {

      add_block(
          // New block address will be directly after the region defined by the
          // previous limit.
          &__heap_start + m_heap_limit, new_limit - m_heap_limit);

      m_heap_limit = new_limit;

      // Coalesce blocks so the new memory joins with the last free block,
      // which is likely to be at the end of previous heap limit.
      coalesce_blocks();
    }
  }

  void merge_adjacent_allocated(block & left, block & right) {
    // Merging two allocations makes the left allocation larger
    // by the size of the right allocation, plus the size of the right
    // allocations node.
    left.m_size += (right.m_size + sizeof(block_node));
  }

private:
  // Nodes are added at the end of the list.
  block_node * add_node(block_node *node) {
    list_node *node_last = m_head;
    for (; node_last->m_next; node_last = node_last->m_next) {
    }

    node_last->m_next = node;
    node->m_prev = node_last;
    return node;
  }

  void add_block(std::byte *address, std::size_t size) {
    // Assume zero alignment padding.
    m_free += add_node(new (address) block_node{size})->m_block.m_size;
    m_used += sizeof(block_node);
  }

  block_node *m_head = nullptr;

public:
  // Heap limit is essentially a global var.  It can
  // be set prior to ctor of blocklist.
  static constexpr std::size_t HEAP_DEFAULT_LIMIT = 4096;
  static std::size_t m_heap_limit;

  // accounting.
  std::size_t m_free = 0;
  std::size_t m_used = 0;
};

blocklist &get_free_list() {
  static blocklist free_list;
  return free_list;
}

// Implement a reallocation by allocating a new region and copying
// old data to new.
void *realloc_copy(void *orig, size_t sz) {
  const auto new_alloc = malloc(sz);
  if (!new_alloc)
    return nullptr;

  const auto orig_sz = block::get_block(static_cast<std::byte *>(orig))->m_size;
  memmove(new_alloc, orig, sz < orig_sz ? sz : orig_sz);
  free(orig);
  return new_alloc;
}

} // namespace

// Heap limit is set to SIZE_MAX at initialization to indicate that
// the size limit has not been set.  If, at the time the heap is initialized,
// the m_heap_limit is still SIZE_MAX, the m_heap_limit will be reset to
// the default limit value.  If the m_heap_limit is not SIZE_MAX when the
// heap is intialized, the user-requsted limit is used.
std::size_t blocklist::m_heap_limit = SIZE_MAX;

extern "C" {

// Weakly-defined malloc and free symbols serve as a call gate
// for default operator new and delete.
__attribute__((weak)) void *malloc(size_t count) {
  auto &free_list = get_free_list();
  return free_list.split_block(free_list.find_first_fit(count), count);
}

__attribute__((weak)) void *realloc(void *orig, size_t count) {
  if (!orig) {
    return malloc(count);
  }

  const auto orig_block_ptr = block::get_block(static_cast<std::byte *>(orig));
  if (count <= orig_block_ptr->m_size) {
    // No reallocation occurs if the requested size isn't increasing. The
    // original allocation is returned.
    return orig;
  }

  auto &free_list = get_free_list();
  const auto grow_sz = count - orig_block_ptr->m_size;

  // Find the adjacent block, and if found split it.
  const auto adjacent_block =
      free_list.find_adjacent_fit(orig_block_ptr, grow_sz);
  if (!adjacent_block) {
    // There was no free space after the current allocation.
    return realloc_copy(orig, count);
  }

  free_list.merge_adjacent_allocated(
      *orig_block_ptr,
      *block::get_block(free_list.split_block(adjacent_block, grow_sz)));
  return orig;
}

__attribute__((weak)) void free(void *ptr) {
  if (!ptr) {
    return;
  }

  auto &free_list = get_free_list();
  free_list.free_block(block::get_block(static_cast<std::byte *>(ptr)));
  free_list.coalesce_blocks();
}

}

__attribute__((weak)) void *operator new(std::size_t count,
                                         const std::nothrow_t &) noexcept {
  // The allocating new functions must allow any user-installed
  // new_handler to retry the allocation by returning.  As long as
  // 1. a new handler is set (get_new_handler returns not null)
  // 2. the new handler returns instead of throwing bad_alloc or terminating.
  // ... then the allocating function must retry the allocation.
  for (;;) {
    const auto block = malloc(count);
    if (block) {
      // Allocation success.
      return block;
    }

    const auto newp = std::get_new_handler();
    if (newp) {
      // User-provided new_handler is set.
      newp();
      // If newp returned, then we retry the loop.  Continue
      // until we succeed in allocation, throw, or get_new_handler returns null.
    }
    else {
      // no user-provided new_handler.
      return nullptr;
    }
  }
}

__attribute__((weak)) void *operator new(std::size_t size) {
  const auto block = operator new(size, std::nothrow);
  if (block) {
    return block;
  }

  // allocation failed and new_handler retry loop must have exited.

  // Standard c++ requires throwing bad_alloc here.
  // TODO: implement throw.
  // Calling terminate here behaves similarly to a caller that
  // does not catch bad_alloc, and therefore has an unhandled exception.
  std::terminate();
}

__attribute__((weak)) void *operator new[](std::size_t size) {
  return operator new(size);
}

__attribute__((weak)) void *operator new[](std::size_t count,
                                           const std::nothrow_t &) noexcept {
  return operator new(count, std::nothrow);
}

__attribute__((weak)) void *operator new(std::size_t, void *ptr) { return ptr; }

__attribute__((weak)) void *operator new[](std::size_t, void *ptr) {
  return ptr;
}

__attribute__((weak)) void operator delete(void *ptr) noexcept { free(ptr); }

__attribute__((weak)) void operator delete[](void *ptr) noexcept {
  operator delete(ptr);
}

namespace std {
namespace {
new_handler current_new_handler = nullptr;
}

new_handler get_new_handler() noexcept { return current_new_handler; }

new_handler set_new_handler(new_handler new_p) noexcept {
  auto old_handler = current_new_handler;
  current_new_handler = new_p;
  return old_handler;
}

const nothrow_t nothrow;

} // namespace std

extern "C" {

size_t __heap_limit() {
  return blocklist::m_heap_limit == SIZE_MAX ? blocklist::HEAP_DEFAULT_LIMIT
                                             : blocklist::m_heap_limit;
}

void __set_heap_limit(size_t new_size) {

  if (blocklist::m_heap_limit == SIZE_MAX) {
    // Heap is uninitialized... set it up for the first call
    blocklist::m_heap_limit = (new_size < blocklist::MIN_ALLOC_SIZE)
                                  ? blocklist::MIN_ALLOC_SIZE
                                  : new_size;
  } else {
    // Heap is initialized.
    get_free_list().set_new_limit(new_size);
  }
}

size_t __heap_bytes_used() { return get_free_list().m_used; }

size_t __heap_bytes_free() { return get_free_list().m_free; }
}
