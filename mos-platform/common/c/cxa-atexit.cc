#include <cstdint>
#include <new>

namespace {

struct ExitFunctionStorage {
  void (*m_functionptr)(void *);
  void *m_userdata;

  void operator()() const { m_functionptr(m_userdata); }
};

/* Exit functions are registered in a singly-linked list of blocks of
 * registrations. Each block contains 32 exit registrations, and additional
 * space for registrations is allocated on the heap, as needed.*/
class RegistrationList {
private:
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

public:
  static bool push_front(const ExitFunctionStorage &new_exit) {

    auto &current_block = *m_list;

    if (!current_block.full()) {
      current_block.push_front(new_exit);
      return true;
    } else {
      const auto next_block = new (std::nothrow) FnNode{m_list};
      if (!next_block) {
        // not enough memory to allocate another exit function
        return false;
      }

      // link new block to front of list.
      next_block->push_front(new_exit);
      m_list = next_block;
      return true;
    }
  }

  static void run_all_exits() {
    while (m_list != &m_tail || !m_list->empty()) {
      if (!m_list->empty()) {
        // Note: fn may itself call atexit, so pop first.
        ExitFunctionStorage fn = m_list->back();
        m_list->pop_back();
        fn();
      } else {
        const auto current_node_ptr = static_cast<FnNode *>(m_list);
        const auto next_block = current_node_ptr->m_next;
        // current_node_ptr is leaked here. We are shutting down.
        m_list = next_block;
      }
    }
  }

private:
  // The initial base node allows 32 exit registrations (1 block)
  // of exit functions, without allocating.  So the minumum required
  // 32 exit functions will always be available.
  static FnBlock m_tail;
  static FnBlock *m_list;
};

// Static allocation of registration list.
RegistrationList::FnBlock RegistrationList::m_tail{};
RegistrationList::FnBlock *RegistrationList::m_list = &m_tail;

} // namespace

extern "C" {

asm(".section .fini.100,\"axR\",@progbits\n"
    "jsr __do_atexit\n");

void __do_atexit() { RegistrationList::run_all_exits(); }

// atexit / finalize are implemented under the assumption that there is only a
// single loaded binary, with no dynamic loading.  Therefore; the mechanism for
// holding a DSO handle (the third parameter to _cxa_atexit), is ignored.
int __cxa_atexit(void (*f)(void *), void *p, void * /* dso_handle */) {
  // Return values equal to C/C++ atexit() return value.
  return !RegistrationList::push_front(ExitFunctionStorage{f, p});
}

} // extern "C"
