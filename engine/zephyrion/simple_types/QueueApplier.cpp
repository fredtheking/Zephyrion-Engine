#include "QueueApplier.hpp"

namespace ZE::ST {
  void QueueApplier::Add(VOID_FUNC_CONST func) {
    queue.push(func);
  }
  void QueueApplier::Invoke() {
    if (!queue.empty())
      for (int i = 0; i < queue.size(); ++i) {
        queue.front()();
        queue.pop();
      }
  }

  QueueApplier::~QueueApplier() {
    Invoke();
  }
}