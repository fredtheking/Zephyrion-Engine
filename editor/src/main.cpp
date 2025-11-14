#include "zephyrion/App.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/configs/WindowConfig.hpp"
#include "zephyrion/core/Logger.hpp"
#include "zephyrion/utils/Util.hpp"

int main() {
  ZE::Util::LogVersion();

  DEFINE_APP_VARIABLE
    app.Create(ZE::Configs::Builders::WindowConfigBuilder{}
      .EnableImGui(ZE::Configs::Builders::ImGuiConfigBuilder{}
        .Process([]{})
        .Build()
      )
      .Build()
    );
}
