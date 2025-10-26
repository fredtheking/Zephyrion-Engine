#pragma once
#include "zephyrion/pch.hpp"
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

      VOID_FUNC process_event = nullptr;
      bool      dark_theme    = true;
    public:
      GETTER(DarkTheme, bool){return dark_theme;}
    };

    namespace Builders {
      class ImguiConfigBuilder final : public Low::BuilderBase<ImguiConfig> {
        void ValidityCheck() override {

        }
      public:
        REF(ImguiConfigBuilder) Process(VOID_FUNC_CONST event) {
          build_object.process_event = event;
          return *this;
        }
        REF(ImguiConfigBuilder) LightTheme() {
          build_object.dark_theme = false;
          return *this;
        }
      };
    }
  }
}
