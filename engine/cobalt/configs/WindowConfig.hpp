 #pragma once
#include "cobalt/core/Logger.hpp"
#include "cobalt/simple_types/Vector2.hpp"
#include "cobalt/utils/Enums.hpp"
#define NONVALID_VEC2 ST::Vector2{NONVALID_INT}


namespace CE {
  class Window;
  namespace Configs {
    namespace Builders {
      class WindowConfigBuilder;
    }

    class WindowConfig {
    private:
      friend class ::CE::Configs::Builders::WindowConfigBuilder;
      friend class ::CE::Window;

      std::string title_str = "Hello from Cobalt Engine!";
      ST::Vector2<int> position_vec2 = NONVALID_VEC2;
      Enums::WindowPosition position_mode_enum = Enums::WindowPosition::Centered;
      ST::Vector2<int> size_vec2 = {800, 600};
      Enums::WindowInitFlags init_flags_enums = Enums::WindowInitFlags::OpenGL;
      Enums::WindowDynamicFlags dynamic_flags_enums = {};
      float opacity_float = 1;
    public:
      GETTER(Title, CREF(std::string)){return title_str;}
      GETTER(Position, CREF(ST::Vector2<int>)){return position_vec2;}
      GETTER(PositionMode, CREF(Enums::WindowPosition)){return position_mode_enum;}
      GETTER(Size, CREF(ST::Vector2<int>)){return size_vec2;}
      GETTER(InitFlags, CREF(Enums::WindowInitFlags)){return init_flags_enums;}
      GETTER(DynamicFlags, CREF(Enums::WindowDynamicFlags)){return dynamic_flags_enums;}
      GETTER(Opacity, CREF(float)){return opacity_float;}
    };

    namespace Builders {
      class WindowConfigBuilder {
        WindowConfig config{};
      public:
        WindowConfigBuilder& Title(CREF(std::string) title) {
          config.title_str = title;
          return *this;
        }
        WindowConfigBuilder& Title(const char* title) {
          return Title(std::string{title});
        }

        WindowConfigBuilder& Position(const Enums::WindowPosition position_mode) {
          config.position_vec2 = NONVALID_VEC2;
          config.position_mode_enum = position_mode;
          return *this;
        }
        WindowConfigBuilder& Position(CREF(ST::Vector2<int>) position) {
          config.position_mode_enum = Enums::WindowPosition::Custom;
          config.position_vec2 = position;
          return *this;
        }
        WindowConfigBuilder& Position(const int x, const int y) {
          return Position(ST::Vector2{x, y});
        }
        WindowConfigBuilder& Position(const float x, const float y) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return Position(ST::Vector2{
            static_cast<int>(x),
            static_cast<int>(y)
          });
        }

        WindowConfigBuilder& Size(CREF(ST::Vector2<int>) size) {
          config.size_vec2 = size;
          return *this;
        }
        WindowConfigBuilder& Size(const int width, const int height) {
          return Size(ST::Vector2{width, height});
        }
        WindowConfigBuilder& Size(const float width, const float height) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return Size(ST::Vector2{
            static_cast<int>(width),
            static_cast<int>(height)
          });
        }

        WindowConfigBuilder& InitFlags(const Enums::WindowInitFlags flags) {
          config.init_flags_enums = flags;
          return *this;
        }

        WindowConfigBuilder& DynamicFlags(const Enums::WindowDynamicFlags flags) {
          config.dynamic_flags_enums = flags;
          return *this;
        }

        WindowConfigBuilder& Opacity(const float opacity) {
          config.opacity_float = opacity;
          return *this;
        }


        WindowConfig Build() {
          return config;
        }
      };
    }
  }
}


#undef NONVALID_VEC2