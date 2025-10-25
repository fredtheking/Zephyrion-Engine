#pragma once
#include "zephyrion/pch.hpp"
#include "configs/AppConfig.hpp"
#include "core/Window.hpp"
#include "core/ImguiHandler.hpp"

namespace ZE {
  class App final {
  private:
    void Initialise();

    void PollInput();
    void Process();
    void Render();
  public:
    void Setup(CREF(Configs::WindowConfig) window_config = {});
    void Run();
    void Terminate();

  private:
    SDL_Event m_Event;
  public:
    bool m_Running = true;
    UPTR(Window) p_MainWindow = nullptr;
    UPTR(Configs::AppConfig) p_Config = nullptr;

    double m_ProcessDeltatime;
    double m_RenderDeltatime;


  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
