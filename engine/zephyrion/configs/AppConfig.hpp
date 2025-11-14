#pragma once
#include "WindowConfig.hpp"
#include "ImguiConfig.hpp"


namespace ZE::Configs {
  struct AppConfig {
    WPTR(WindowConfig) window;
  };
}
