#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/core/Logger.hpp"
#include "zephyrion/low/BuilderBase.hpp"

namespace ZE {
  class ImguiHandler;
  namespace Configs {
    namespace Builders {
      class ImguiConfigBuilder;
    }

    class ImguiConfig {
    private:
      friend class ::ZE::Configs::Builders::ImguiConfigBuilder;
      friend class ::ZE::ImguiHandler;

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
      class ImguiConfigBuilder final : public Low::BuilderBase<ImguiConfig> {
        void ValidityCheck() override {
          if (build_object.docking_bool)
            Logger::Warning("Warning in \"ImguiConfig\" - "
              "\"Docking\" is enabled; background color may be altered.");
        }
      public:
        REF(ImguiConfigBuilder) Process(VOID_FUNC_CONST event) {
          build_object.process_event = event;
          return *this;
        }
        REF(ImguiConfigBuilder) LightTheme() {
          build_object.dark_theme_bool = false;
          return *this;
        }
        REF(ImguiConfigBuilder) Docking() {
          build_object.docking_bool = true;
          return *this;
        }
        REF(ImguiConfigBuilder) FloatingWindows() {
          build_object.floating_windows_bool = true;
          return *this;
        }
      };
    }
  }
}
