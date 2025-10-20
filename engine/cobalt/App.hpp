#pragma once
#include "cobalt/pch.hpp"
#include "configs/AppConfig.hpp"
#include "core/Window.hpp"
#include "utils/Macros.hpp"

namespace CE {
  class App final {
  private:
    void Initialise();
    void Terminate();

    void Process();
    void Render() const;
  public:
    void Setup(CREF(Configs::WindowConfig) window_config);
    void Run();
    void Shutdown();

  private:
    //...
  public:
    bool m_Running = true;
    UPTR(Window) p_MainWindow;
    UPTR(Configs::AppConfig) p_Config;


  private:
    //...
  public:
    SINGLETON_CONSTRUCTOR(App)
  };
}
