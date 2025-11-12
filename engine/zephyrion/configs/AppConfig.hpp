#pragma once
#include "WindowConfig.hpp"
#include "ImGuiConfig.hpp"


namespace ZE::Configs {
  struct AppConfig {
    WPTR(WindowConfig) window;
  };
}
