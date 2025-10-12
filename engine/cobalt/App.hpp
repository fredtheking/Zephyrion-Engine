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
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
  public:
    bool m_Running = true;

  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
