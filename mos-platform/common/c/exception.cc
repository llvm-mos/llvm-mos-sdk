#include <exception>
#include <stdlib.h>

namespace std {
// __current_terminate_handler shall be never-null.
// It's either abort() or the function provided at set_terminate.
static terminate_handler __current_terminate_handler = ::abort;

// Current standard explicilty says the default handler value does not have to
// be nullptr.
terminate_handler get_terminate() noexcept {
  return __current_terminate_handler;
}

terminate_handler set_terminate(terminate_handler f) noexcept {
  const auto old_terminate_handler = __current_terminate_handler;
  __current_terminate_handler = (f != nullptr) ? f : ::abort;
  return old_terminate_handler;
}

[[noreturn]] void terminate() noexcept {
  __current_terminate_handler();
  __builtin_unreachable();
}
} // namespace std
