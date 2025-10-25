#pragma once
#include "Window.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/ImguiConfig.hpp"

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
    //...
  public:
    explicit ImguiHandler(REF(Configs::ImguiConfig) imgui_config, CREF(Window) window);
    ~ImguiHandler();
  };
}
