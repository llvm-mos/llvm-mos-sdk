#include <new>
#include <stdint.h>
#include <stdio.h>
#define _MOS_SOURCE 1
#include <stdlib.h>

namespace {
struct a_large_struct
{
  a_large_struct()
  : an_array{ 5, 4, 3, 2, 1 }
  {
  }

  char an_array[129];
};

template <class T, size_t N>
constexpr size_t static_size(const T (&)[N])
{
  return N;
}

} // namespace

int main() {
  printf("DEFAULT HEAP IS %d BYTES\n", heap_limit());

  {
    const auto an_alloc = new a_large_struct();
    printf("ALLOCATED 500 BYTES AT $%p\n", an_alloc);
    delete an_alloc;
  }

  {
    // For non-throwing allocationg, std::nothrow must be used.
    const auto an_alloc = new (std::nothrow) unsigned char[40000];
    if (!an_alloc) {
      puts("ALLOCATION FOR 40000 BYTES FAILED");
    } else {
      printf("ALLOCATED 40000 BYTES AT %p\n", an_alloc);
    }
  }

  {

    // Using the heap limit functionality.  Default heap limit
    // is shown above.

    // Use the heap to allocate pointers to some allocations:
    constexpr auto ALLOC_COUNT = 1000;
    const auto vector_of_ptrs = new std::size_t *[ALLOC_COUNT];

    printf("READY TO FILL THE HEAP. BYTES IN USE SO FAR: %u\n", ::heap_bytes_used());

    for (std::size_t j = 0; j < ALLOC_COUNT; j += 1) {
      vector_of_ptrs[j] = nullptr;
    }

    std::size_t i = 0;

    // Fill the heap with allocations until it fails.
    for (; i < ALLOC_COUNT; i += 1) {
      auto int_ptr = new (std::nothrow) std::size_t{i};
      if (!int_ptr) {
        printf("HEAP ALLOCATION FAILED AFTER ALLOCATING %u TIMES\n", i);
        printf("BYTES IN USE: %u\n", ::heap_bytes_used());
        break;
      }

      vector_of_ptrs[i] = int_ptr;
    }

    // Increase the heap limit.
    const auto new_limit = ::heap_limit() + 8192;
    printf("SETTING HEAP LIMIT TO %u\n", new_limit);
    ::set_heap_limit(new_limit);

    for (; i < 1000; i += 1) {
      // use throwing allocations-- these should all succeed since we
      // increased the size of the heap.
      vector_of_ptrs[i] = new std::size_t{i};
    }

    printf("FINISHED ALLOCATIONS. USING %u BYTES.\n", ::heap_bytes_used());
    for (i = 0; i < ALLOC_COUNT; i += 1) {
      delete vector_of_ptrs[i]; // manual delete required for raw ptrs.
    }

    delete [] vector_of_ptrs;
  }

  // At the end of the program, there should only be a few bytes in use by the
  // heap's internal data structures.  For example, assuming the heap combined
  // all freed blocks of memory, there should just be the overhead of a single
  // block description
  printf("HEAP IN USE AT END OF PROGRAM IS %u\n", ::heap_bytes_used());
  return 0;
}
