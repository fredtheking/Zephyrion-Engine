#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/ImguiConfig.hpp"
#include "zephyrion/low/DetachedProcess.hpp"

namespace ZE {
  class ImguiHandler {
  private:
    //...
  public:
    //...

  private:
    REF(Configs::ImguiConfig) p_Config;
    Low::DetachedProcess e_ImguiProcess;
  public:
    //...

  private:
    //...
  public:
    explicit ImguiHandler(REF(Configs::ImguiConfig) imgui_config);
    ~ImguiHandler();
  };
}
