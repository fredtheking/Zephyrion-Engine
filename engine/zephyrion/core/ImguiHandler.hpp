#pragma once
#include "Window.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/ImguiConfig.hpp"
#include "zephyrion/simple_types/QueueApplier.hpp"

namespace ZE {
  class ImguiHandler {
  private:
    //...
  public:
    void Render() const;
    void Draw() const;

  private:
    REF(Configs::ImguiConfig) p_Config;
    CREF(Window) p_MainWindow;
  public:
    //...

  private:
    friend class App;
  public:
    explicit ImguiHandler(CREF(Window) window);
    ~ImguiHandler();
  };
}
