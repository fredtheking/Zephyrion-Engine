#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/utils/Macros.hpp"

namespace CE {
  class Window {
  private:
    //...
  public:
    //...

  private:
    SDL_Window* p_Window;
    SDL_Renderer* p_Renderer;
  public:
    std::vector<SPTR(Window)> m_WindowChildren;

  private:
    friend class App;
  public:
    Window(int width, int height, CREF(std::string) title, SDL_WindowFlags flags);
    ~Window();
  };
}