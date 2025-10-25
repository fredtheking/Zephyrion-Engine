#pragma once
#include "ImguiHandler.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/WindowConfig.hpp"
#include "zephyrion/simple_types/Bounds.hpp"

namespace ZE {
  class Window {
  private:
    void Internal_UpdateWindowPosition() const;
    void Internal_UpdateWindowSizeConfigs() const;
    void Internal_UpdateWindowSize() const;
    void Internal_SetWindowMinimaxSize() const;
    [[nodiscard]] SDL_WindowFlags Internal_InitialiseFlags() const;
    void Internal_AfterWindowInit();
  public:
    void UpdateIcon(CREF(std::string) filepath);

    void UpdatePosition(Enums::ZE_WindowPosition position_mode) const;
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
    void SetHidden(bool value) const;

  private:
    //...
  public:
    REF(Configs::WindowConfig) p_Config;
    OPT(UPTR(ImguiHandler)) m_Imgui = NULLOPT;
    SDL_GLContext m_GLContext = nullptr;
    SDL_Window* p_Window = nullptr;
    SDL_Surface* p_Icon = nullptr;

    std::vector<SPTR(Window)> m_WindowChildren = {};

  private:
    friend class App;
  public:
    explicit Window(REF(Configs::WindowConfig) window_config);
    ~Window();
  };
}