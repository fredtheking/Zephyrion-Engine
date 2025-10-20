#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/configs/WindowConfig.hpp"
#include "cobalt/utils/Macros.hpp"

namespace CE {
  class Window {
  private:
    void Internal_UpdateWindowPosition() const;
    void Internal_UpdateWindowSize() const;
    void Internal_SetWindowMinimaxSize() const;
    [[nodiscard]] SDL_WindowFlags Internal_InitialiseFlags() const;
    void Internal_AfterWindowInit();
  public:
    void UpdateIcon(CREF(std::string) filepath);

    void UpdatePosition(Enums::WindowPosition position_mode) const;
    void UpdatePosition(CREF(ST::Vector2<int>) position) const;
    void UpdatePosition(CREF(ST::Vector2<>) position) const;
    void UpdatePosition(int x, int y) const;
    void UpdatePosition(float x, float y) const;
    void UpdateSize(CREF(ST::Vector2<int>) size) const;
    void UpdateSize(CREF(ST::Vector2<>) size) const;
    void UpdateSize(int width, int height) const;
    void UpdateSize(float width, float height) const;
    void SetResizable(bool value) const;
    void SetBorderless(bool value) const;
    void SetFullscreen(bool value) const;
    void SetAlwaysOnTop(bool value) const;

  private:
    //...
  public:
    REF(Configs::WindowConfig) p_Config;
    SDL_Window* p_Window;
    SDL_Renderer* p_Renderer;
    SDL_Surface* p_Icon;

    std::vector<SPTR(Window)> m_WindowChildren;

  private:
    friend class App;
  public:
    explicit Window(REF(Configs::WindowConfig) window_config);
    ~Window();
  };
}