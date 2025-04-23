#include <new>

#include <cstdlib>
#include <exception>

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
    } else {
      // no user-provided new_handler.
      return nullptr;
    }
  }
}

__attribute__((weak)) void *operator new(std::size_t size) {
  const auto block = operator new(size, std::nothrow);
  if (block)
    return block;

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

__attribute__((weak)) void operator delete(void *ptr, std::size_t) noexcept {
  operator delete(ptr);
}

__attribute__((weak)) void operator delete[](void *ptr, std::size_t) noexcept {
  operator delete(ptr);
}

static std::new_handler current_new_handler = nullptr;

namespace std {

new_handler get_new_handler() noexcept { return current_new_handler; }

new_handler set_new_handler(new_handler new_p) noexcept {
  auto old_handler = current_new_handler;
  current_new_handler = new_p;
  return old_handler;
}

const nothrow_t nothrow;

} // namespace std
