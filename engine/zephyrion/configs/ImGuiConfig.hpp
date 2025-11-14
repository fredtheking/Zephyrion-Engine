#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/core/Logger.hpp"
#include "zephyrion/low/BuilderBase.hpp"

namespace ZE {
  class ImGuiHandler;
  namespace Configs {
    namespace Builders {
      class ImGuiConfigBuilder;
    }

    class ImGuiConfig {
    private:
      friend class ::ZE::Configs::Builders::ImGuiConfigBuilder;
      friend class ::ZE::ImGuiHandler;

      VOID_FUNC process_event        = nullptr;
      bool      dark_theme_bool      = true;
      bool      docking_bool         = false;
      bool      floating_windows_bool = false;
    public:
      GETTER(DarkTheme, bool){return dark_theme_bool;}
      GETTER(Docking, bool){return docking_bool;}
      GETTER(FloatingWindows, bool){return floating_windows_bool;}
    };

    namespace Builders {
      class ImGuiConfigBuilder final : public Low::BuilderBase<ImGuiConfig> {
        void ValidityCheck() override {
          if (build_object.docking_bool)
            Logger::Warning("Warning in \"ImGuiConfig\" - "
              "\"Docking\" is enabled; background color may be altered.");
        }
      public:
        REF(ImGuiConfigBuilder) Process(VOID_FUNC_CONST event) {
          build_object.process_event = event;
          return *this;
        }
        REF(ImGuiConfigBuilder) LightTheme() {
          build_object.dark_theme_bool = false;
          return *this;
        }
        REF(ImGuiConfigBuilder) Docking() {
          build_object.docking_bool = true;
          return *this;
        }
        REF(ImGuiConfigBuilder) FloatingWindows() {
          build_object.floating_windows_bool = true;
          return *this;
        }
      };
    }
  }
}
