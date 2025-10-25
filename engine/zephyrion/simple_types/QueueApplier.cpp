#include "QueueApplier.hpp"

void ZE::ST::QueueApplier::Add(VOID_FUNC_CONST func) {
  queue.push(func);
}
void ZE::ST::QueueApplier::Invoke() {
  if (!queue.empty())
    for (int i = 0; i < queue.size(); ++i) {
      queue.front()();
      queue.pop();
    }
}

ZE::ST::QueueApplier::~QueueApplier() {
  Invoke();
}
