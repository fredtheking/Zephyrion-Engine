#pragma once
#include "WindowConfig.hpp"

namespace CE::Configs {
  struct AppConfig {
    SPTR(WindowConfig) window;
  };
}
