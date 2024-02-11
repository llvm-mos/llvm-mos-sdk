#ifndef ATEXIT_IMPL_H
#define ATEXIT_IMPL_H

#include <cstdint>

namespace __impl {

struct ExitFunctionStorage {
  void (*m_functionptr)(void *);
  void *m_userdata;

  void operator()() const { m_functionptr(m_userdata); }
};

/* Exit functions are registered in a singly-linked list of blocks of
 * registrations. Each block contains 32 exit registrations, and additional
 * space for registrations is allocated on the heap, as needed.*/
class RegistrationList {
  // FnBlock is an array of function pointers and their arguments.
  // The logical "front" of the block is the last item appended to
  // the array.
  struct FnBlock {
    static constexpr std::uint8_t BLOCK_SZ = 32;

    ExitFunctionStorage m_funcs[BLOCK_SZ];
    std::uint8_t m_sz;

    bool empty() const { return !m_sz; }
    bool full() const { return m_sz == BLOCK_SZ; }

    void push_front(const ExitFunctionStorage &newfn) {
      m_funcs[m_sz++] = newfn;
    }

    const ExitFunctionStorage &back() const { return m_funcs[m_sz - 1]; }
    void pop_back() { m_sz--; }
  };

  struct FnNode : public FnBlock {
    FnNode(FnBlock *next) : m_next{next} {}

    FnBlock *const m_next = nullptr;
  };

  // The initial base node allows 32 exit registrations (1 block)
  // of exit functions, without allocating.  So the minumum required
  // 32 exit functions will always be available.
  FnBlock m_tail;
  FnBlock *m_list = &m_tail;

public:
  bool push_front(const ExitFunctionStorage &new_exit);
  void run_all_exits();
};

} // namespace __impl

#endif // not ATEXIT_IMPL_H
