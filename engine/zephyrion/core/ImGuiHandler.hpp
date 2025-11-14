#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/ImGuiConfig.hpp"

namespace ZE {
  class Window;

  class ImGuiHandler {
  private:
    //...
  public:
    void Render() const;
    void Draw() const;

  private:
    REF(Configs::ImGuiConfig) p_Config;
    CREF(Window) p_MainWindow;
  public:
    //...

  private:
    friend class App;
  public:
    explicit ImGuiHandler(CREF(Window) window);
    ~ImGuiHandler();
  };
}
