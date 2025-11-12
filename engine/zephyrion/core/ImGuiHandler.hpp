#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/ImGuiConfig.hpp"

namespace ZE {
  class Window;

  template<typename T>
  class ImGuiHandler {
  private:
    INTERNAL_GUARD_BEGIN
    void Internal_SpecificInit();
    void Internal_SpecificShutdown();
    void Internal_SpecificNewFrame();
    void Internal_SpecificRenderDrawData();
    void Internal_SpecificFloatingEndAction();
    INTERNAL_GUARD_END
  public:
    void Render() const;
    void Draw() const;

  private:
    CREF(Configs::ImGuiConfig) p_Config;
    CREF(Window) p_LinkedWindow;
  public:
    //...

  private:
    friend class App;
  public:
    explicit ImGuiHandler(CREF(Window) window);
    ~ImGuiHandler();
  };
}


