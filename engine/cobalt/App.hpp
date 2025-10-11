#pragma once
#include "cobalt/pch.hpp"
#include "utils/Macros.hpp"

namespace Cobalt {
  class App final {
  private:
    void Process();
    void Render();
  public:
    void Run();

  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
