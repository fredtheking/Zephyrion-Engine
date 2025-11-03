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
    void Internal_HandleResize();

    void Process();
    void Render();
  public:
    void UpdateIcon(CREF(STR) filepath);

    void UpdatePosition(Enums::ZE_WindowPosition position_mode) const;
    void UpdatePosition(CREF(ST_VEC2(int)) position) const;
    void UpdatePosition(CREF(ST_VEC2()) position) const;
    void UpdatePosition(int x, int y) const;
    void UpdatePosition(float x, float y) const;
    void UpdateSize(CREF(ST_VEC2(int)) size) const;
    void UpdateSize(CREF(ST_VEC2()) size) const;
    void UpdateSize(int width, int height) const;
    void UpdateSize(float width, float height) const;
    void SetResizable(bool value) const;
    void SetBorderless(bool value) const;
    void SetFullscreen(bool value) const;
    void SetAlwaysOnTop(bool value) const;
    void SetHidden(bool value) const;
    void SetVsync(bool value) const;

  private:
    //...
  public:
    /**
     * The only holder of window config. Access this variable only via weak_ptrs or directly.
     */
    SPTR(Configs::WindowConfig) p_Config;
    /**
     * Optional imgui handler for current window.
     */
    OPT(UPTR(ImguiHandler)) m_Imgui = NULLOPT;
    SDL_GLContext m_GLContext = nullptr;
    SDL_Window* p_Window = nullptr;
    SDL_Surface* p_Icon = nullptr;

  private:
    friend class App;
  public:
    explicit Window(CREF(Configs::WindowConfig) window_config);
    ~Window();
  };
}