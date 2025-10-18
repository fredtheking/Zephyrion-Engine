 #pragma once
#include "cobalt/core/Logger.hpp"
#include "cobalt/low/BuilderBase.hpp"
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

      Enums::BackendRenderer renderer_enum = Enums::BackendRenderer::OpenGL;
      std::string title_str = "Hello from Cobalt Engine!";
      ST::Vector2<int> position_vec2 = NONVALID_VEC2;
      Enums::WindowPosition position_mode_enum = Enums::WindowPosition::Centered;
      ST::Vector2<int> size_vec2 = {800, 600};
      float opacity_float = 1;

      bool resizable_bool = false;
      bool borderless_bool = false;
      bool fullscreen_bool = false;
    public:
      GETTER(BackendRendererName, std::string_view){return magic_enum::enum_name(renderer_enum);}
      GETTER(Title, CREF(std::string)){return title_str;}
      GETTER(Position, CREF(ST::Vector2<int>)){return position_vec2;}
      GETTER(PositionMode, CREF(Enums::WindowPosition)){return position_mode_enum;}
      GETTER(Size, CREF(ST::Vector2<int>)){return size_vec2;}
      GETTER(Opacity, CREF(float)){return opacity_float;}
    };

    namespace Builders {
      class WindowConfigBuilder final : public Low::BuilderBase<WindowConfig> {
      public:
        WindowConfigBuilder& BackendRenderer(const Enums::BackendRenderer renderer) {
          build_object.renderer_enum = renderer;
          return *this;
        }

        WindowConfigBuilder& Title(CREF(std::string) title) {
          build_object.title_str = title;
          return *this;
        }
        WindowConfigBuilder& Title(const char* title) {
          return Title(std::string{title});
        }

        WindowConfigBuilder& Position(const Enums::WindowPosition position_mode) {
          build_object.position_vec2 = NONVALID_VEC2;
          build_object.position_mode_enum = position_mode;
          return *this;
        }
        WindowConfigBuilder& Position(CREF(ST::Vector2<int>) position) {
          build_object.position_mode_enum = Enums::WindowPosition::Custom;
          build_object.position_vec2 = position;
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
          build_object.size_vec2 = size;
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

        WindowConfigBuilder& Opacity(const float opacity) {
          build_object.opacity_float = opacity;
          return *this;
        }


        WindowConfig Build() override {
          if (build_object.renderer_enum != Enums::BackendRenderer::OpenGL)
            Logger::Critical("Incorrect \"WindowConfig\"! - "
              "Currently, only \"OpenGL\" backend renderer is supported.");

          if (build_object.position_vec2 == NONVALID_VEC2 &&
              build_object.position_mode_enum == Enums::WindowPosition::Custom)
            Logger::Critical("Incorrect \"WindowConfig\"! - "
              "If you are using \"CE::Enums::WindowPosition\" to define position, it is prohibited to use \"Custom\" option. Instead, use real values.");

          return std::move(build_object);
        }
      };
    }
  }
}

#undef NONVALID_VEC2
