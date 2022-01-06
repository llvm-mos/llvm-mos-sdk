#include <new>
#include <stdint.h>
#include <stdio.h>
#define _MOS_SOURCE 1
#include <stdlib.h>

#define VERBOSE 1

#if VERBOSE
#define logva printf
#else
void logva(const char *s, ...) {}
#endif

namespace {
// recreate std::move and std::unique_ptr<T[]>
template <class T> T &&move(T &src) { return static_cast<T &&>(src); }

template <class T> struct unique_ptr {
  unique_ptr(std::size_t N) : m_ptr{new T[N]} {}
  unique_ptr(std::size_t N, std::nothrow_t) : m_ptr{new (std::nothrow) T[N]} {}
  unique_ptr() = default;
  unique_ptr(const unique_ptr &) = delete;

  unique_ptr(unique_ptr &&src) : m_ptr{src.m_ptr} { src.m_ptr = nullptr; }

  unique_ptr &operator=(unique_ptr &&src) {
    delete[] m_ptr;
    m_ptr = src.m_ptr;
    src.m_ptr = nullptr;
    return *this;
  }

  unique_ptr &operator=(const unique_ptr &) = delete;

  T &operator[](uint8_t idx) { return m_ptr[idx]; }
  T &operator[](std::size_t idx) { return m_ptr[idx]; }
  const T &operator[](uint8_t idx) const {
    return const_cast<unique_ptr *>(this)->operator[](idx);
  }
  T &operator[](std::size_t idx) const {
    return const_cast<unique_ptr *>(this)->operator[](idx);
  }

  ~unique_ptr() { delete[] m_ptr; }
  T *get() const { return m_ptr; }
  operator bool() const { return m_ptr != nullptr; }
  T *m_ptr = nullptr;
};

template <class T, size_t N> constexpr size_t static_size(const T (&)[N]) {
  return N;
}
} // namespace

extern std::byte __heap_start;

int main() {
  logva("DEFAULT HEAP IS %d BYTES\n", heap_limit());

  {
    unique_ptr<char> an_alloc{500};
    logva("ALLOCATED 500 BYTES AT %p\n", an_alloc.get());
  }

  {
    unique_ptr<char> an_alloc{40000, std::nothrow};
    if (!an_alloc) {
      puts("ALLOCATION FOR 40000 BYTES FAILED");
    } else {
      logva("ALLOCATED 40000 BYTES AT %p\n", an_alloc.get());
    }
  }

  static constexpr uint8_t alloc_sizes[] = {1, 4, 16, 7, 35, 100, 3, 9};
  static constexpr auto ALLOC_COUNT = static_size(alloc_sizes);
  // TODO: implement __cxa_atexit
  // for c++ objects with destructors that are declared at static or global
  // scope
  unique_ptr<uint8_t> allocations[ALLOC_COUNT] = {};

  for (uint8_t i = 0; i < ALLOC_COUNT; i += 1) {
    const auto alloc_sz = alloc_sizes[i];
    unique_ptr<uint8_t> new_alloc{alloc_sz};

    logva("ALLOCATED %u BYTES AT %p\n", static_cast<unsigned>(alloc_sz),
          new_alloc.get());

    for (uint8_t j = 0; j < alloc_sz; j += 1) {
      new_alloc[j] = alloc_sz;
    }
    allocations[i] = move(new_alloc);
  }

  // dealloc in a different order than alloc
  static uint8_t dealloc_order[ALLOC_COUNT] = {4, 6, 2, 0, 3, 1, 7, 5};

  for (uint8_t i = 0; i < ALLOC_COUNT; i += 1) {
    const auto test_alloc_idx = dealloc_order[i];
    const unique_ptr<uint8_t> alloc_to_test = move(allocations[test_alloc_idx]);
    const auto test_alloc_size = alloc_sizes[test_alloc_idx];

    logva("CHECKING ALLOCATION OF %u BYTES AT %p\n", test_alloc_size,
          alloc_to_test.get());

    for (uint8_t j = 0; j < test_alloc_size; j += 1) {
      if (alloc_to_test[j] != test_alloc_size) {
        logva("UNEXPECTED VALUE STORED IN HEAP: EXPECT %u, ACTUAL %u\n",
              static_cast<unsigned>(test_alloc_size),
              static_cast<unsigned>(alloc_to_test[j]));
        return 1;
      }
    }
  }

  {
    printf("HEAP IS FROM $%p TO $%p\n", &__heap_start,
           &__heap_start + ::heap_limit());

    // heap limiting tests
    // Use the heap to allocate pointers to some allocations:
    constexpr auto ALLOC_COUNT = 1000;
    unique_ptr<std::size_t *> vector_of_ptrs{ALLOC_COUNT, std::nothrow};

    printf("BYTES IN USE: %u\n", ::heap_bytes_used());

    for (std::size_t j = 0; j < ALLOC_COUNT; j += 1) {
      vector_of_ptrs[j] = nullptr;
    }

    std::size_t i = 0;

    for (; i < ALLOC_COUNT; i += 1) {
      auto int_ptr = new (std::nothrow) std::size_t{i};
      if (!int_ptr) {
        printf("HEAP ALLOCATION FAILED AFTER ALLOCATING %u TIMES\n", i);
        printf("BYTES IN USE: %u\n", ::heap_bytes_used());
        break;
      }

      vector_of_ptrs[i] = int_ptr;
    }

    const auto new_limit = ::heap_limit() + 8192;
    printf("SETTING HEAP LIMIT TO %u\n", new_limit);
    ::set_heap_limit(new_limit);
    for (; i < 1000; i += 1) {
      vector_of_ptrs[i] = new std::size_t{i};
    }

    printf("FINISHED ALLOCATIONS. USING %u BYTES.\n", ::heap_bytes_used());
    for (i = 0; i < ALLOC_COUNT; i += 1) {
      delete vector_of_ptrs[i]; // manual delete required for raw ptrs.
    }
  }

  puts("NEW AND DELETE WORKS");

  // At the end of the program, there should only be a few bytes in use by the
  // heap's internal data structures.  For example, assuming the heap combined
  // all freed blocks of memory, there should just be the overhead of a single
  // block description
  logva("HEAP IN USE AT END OF PROGRAM IS %u\n", ::heap_bytes_used());
  // dump();
  return 0;
}
