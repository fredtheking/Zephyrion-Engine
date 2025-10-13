#pragma once
#include "cobalt/pch.hpp"
#include "core/Window.hpp"
#include "utils/Macros.hpp"

namespace Cobalt {
  class App final {
  private:
    void Setup();
    void Terminate();

    void Process();
    void Render();
  public:
    void Run();

  private:
    //...
  public:
    bool m_Running = true;
    UPTR(Window) p_MainWindow;

  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
