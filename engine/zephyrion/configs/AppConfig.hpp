#pragma once
#include "WindowConfig.hpp"
#include "ImguiConfig.hpp"


namespace ZE::Configs {
  struct AppConfig {
    UPTR(WindowConfig) window;
    UPTR(ImguiConfig) imgui;
  };
}
