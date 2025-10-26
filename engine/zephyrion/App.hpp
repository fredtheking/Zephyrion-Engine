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
    SDL_Event m_Event{};
    VEC(WPTR(Window)) m_Windows = {};
  public:
    bool m_Running = true;
    SPTR(Window) p_MainWindow = nullptr;
    UPTR(Configs::AppConfig) p_Config = nullptr;

    double m_ProcessDeltatime = 0;
    double m_RenderDeltatime = 0;


  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
