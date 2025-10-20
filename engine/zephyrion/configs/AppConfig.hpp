#pragma once
#include "WindowConfig.hpp"

namespace ZE::Configs {
  struct AppConfig {
    SPTR(WindowConfig) window;
  };
}
