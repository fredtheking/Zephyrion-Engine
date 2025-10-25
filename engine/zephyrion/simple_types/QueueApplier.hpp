#pragma once
#include "zephyrion/pch.hpp"

namespace ZE::ST {
  class QueueApplier {
  private:
    //...
  public:
    void Add(VOID_FUNC_CONST func);
    void Invoke();

  private:
    std::queue<VOID_FUNC> queue;
  public:
    //...

  private:
    //...
  public:
    QueueApplier() = default;
    ~QueueApplier();
  };
}