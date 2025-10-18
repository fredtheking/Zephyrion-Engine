#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/configs/WindowConfig.hpp"
#include "cobalt/utils/Macros.hpp"

namespace CE {
  class Window {
  private:
    void Internal_SetWindowPosition() const;
    [[nodiscard]] SDL_WindowFlags Internal_InitialiseFlags() const;
  public:
    void UpdateIcon(CREF(std::string) filepath);

  private:
    SPTR(Configs::WindowConfig) p_Config;
    SDL_Window* p_Window;
    SDL_Renderer* p_Renderer;
    SDL_Surface* p_Icon;
  public:
    std::vector<SPTR(Window)> m_WindowChildren;

  private:
    friend class App;
  public:
    explicit Window(CREF(SPTR(Configs::WindowConfig)) window_config);
    ~Window();
  };
}