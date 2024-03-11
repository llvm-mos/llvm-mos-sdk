#include "atexit-impl.h"

#include <new>

using namespace __impl;

bool RegistrationList::push_front(const ExitFunctionStorage &new_exit) {
  auto &current_block = *m_list;

  if (!current_block.full()) {
    current_block.push_front(new_exit);
    return true;
  }

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

void RegistrationList::run_all_exits() {
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

