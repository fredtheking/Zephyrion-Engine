#pragma once
#include "ImguiConfig.hpp"
#include "zephyrion/core/Logger.hpp"
#include "zephyrion/low/BuilderBase.hpp"
#include "zephyrion/simple_types/Vector2.hpp"
#include "zephyrion/utils/Enums.hpp"

namespace ZE {
  class Window;
  namespace Configs {
    namespace Builders {
      class WindowConfigBuilder;
    }

    class WindowConfig {
    private:
      friend class ::ZE::Configs::Builders::WindowConfigBuilder;
      friend class ::ZE::Window;
      friend class ::ZE::ImguiHandler;

      Enums::ZE_BackendRenderer renderer_enum       = Enums::ZE_BackendRenderer::OpenGL;
      STR title_str                                 = "Hello from Zephyrion Engine!";
      STR icon_filepath_str                         = "";
      OPT(ST::Vector2<int>) position_vec2           = NULLOPT;
      Enums::ZE_WindowPosition position_mode_enum   = Enums::ZE_WindowPosition::Centered;
      ST::Vector2<int> size_vec2                    = {800, 600};
      OPT(ST::Vector2<int>) max_size_vec2           = NULLOPT;
      OPT(ST::Vector2<int>) min_size_vec2           = NULLOPT;
      OPT(float) opacity_float                      = NULLOPT;
      bool vsync_bool                               = true;
      std::optional<ImguiConfig> imgui_config       = NULLOPT;

      bool resizable_bool                           = false;
      bool borderless_bool                          = false;
      bool fullscreen_bool                          = false;
      bool always_on_top_bool                       = false;
      bool hidden_bool                              = false;
      bool input_blocked_bool                       = false;

      SDL_Window* modal_parent_pointer              = nullptr;
      bool external_bool                            = false;
    public:
      GETTER(BackendRendererName, STR){return STR{magic_enum::enum_name(renderer_enum)};}
      GETTER(Title, CREF(STR)){return title_str;}
      GETTER(Position, ST::Vector2<int>){return position_vec2.has_value() ? position_vec2.value() : NONVALID_ST_VEC2;}
      GETTER(PositionMode, CREF(Enums::ZE_WindowPosition)){return position_mode_enum;}
      GETTER(Size, CREF(ST::Vector2<int>)){return size_vec2;}
      GETTER(MaximumSize, ST::Vector2<int>){return max_size_vec2.has_value() ? max_size_vec2.value() : NONVALID_ST_VEC2;}
      GETTER(MinimalSize, ST::Vector2<int>){return min_size_vec2.has_value() ? min_size_vec2.value() : NONVALID_ST_VEC2;}
      GETTER(Opacity, float){return opacity_float.has_value() ? opacity_float.value() : NONVALID_FLOAT;}
      GETTER(VSync, bool){return vsync_bool;}
      GETTER(ImGuiConfig, CREF(OPT(ImguiConfig))){return imgui_config;}
    };

    namespace Builders {
      class WindowConfigBuilder final : public Low::BuilderBase<WindowConfig> {
        void ValidityCheck() override {
          if (build_object.renderer_enum != Enums::ZE_BackendRenderer::OpenGL)
            Logger::Critical("Incorrect \"WindowConfig\"! - "
              "Currently, only \"OpenGL\" backend renderer is supported.");

          if (build_object.position_vec2 == NONVALID_ST_VEC2 &&
              build_object.position_mode_enum == Enums::ZE_WindowPosition::Custom)
            Logger::Critical("Incorrect \"WindowConfig\"! - "
              "If you are using \"ZE::Enums::WindowPosition\" to define position, it is prohibited to use \"Custom\" option. Instead, use real values.");
        }
      public:
        REF(WindowConfigBuilder) BackendRenderer(const Enums::ZE_BackendRenderer renderer) {
          build_object.renderer_enum = renderer;
          return *this;
        }

        REF(WindowConfigBuilder) Resizable() {
          build_object.resizable_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) Borderless() {
          build_object.borderless_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) Fullscreen() {
          build_object.fullscreen_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) AlwaysOnTop() {
          build_object.always_on_top_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) Hidden() {
          build_object.hidden_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) InputBlocked() {
          build_object.input_blocked_bool = true;
          return *this;
        }
        REF(WindowConfigBuilder) Modal(SDL_Window* parent) {
          build_object.modal_parent_pointer = parent;
          return *this;
        }
        REF(WindowConfigBuilder) External() {
          build_object.external_bool = true;
          return *this;
        }

        REF(WindowConfigBuilder) Title(CREF(std::string) title) {
          build_object.title_str = title;
          return *this;
        }
        REF(WindowConfigBuilder) Title(const char* title) {
          return Title(std::string{title});
        }

        REF(WindowConfigBuilder) Icon(CREF(std::string) filepath) {
          build_object.icon_filepath_str = filepath;
          return *this;
        }

        REF(WindowConfigBuilder) Position(const Enums::ZE_WindowPosition position_mode) {
          build_object.position_vec2 = NULLOPT;
          build_object.position_mode_enum = position_mode;
          return *this;
        }
        REF(WindowConfigBuilder) Position(CREF(ST::Vector2<int>) position) {
          build_object.position_mode_enum = Enums::ZE_WindowPosition::Custom;
          build_object.position_vec2 = position;
          return *this;
        }
        REF(WindowConfigBuilder) Position(CREF(ST::Vector2<>) size) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return Position(ST::Vector2{
            static_cast<int>(size.x),
            static_cast<int>(size.y)
          });
        }
        REF(WindowConfigBuilder) Position(const int x, const int y) {
          return Position(ST::Vector2{x, y});
        }
        REF(WindowConfigBuilder) Position(const float x, const float y) {
          return Position(ST::Vector2{x, y});
        }

        REF(WindowConfigBuilder) Size(CREF(ST::Vector2<int>) size) {
          build_object.size_vec2 = size;
          return *this;
        }
        REF(WindowConfigBuilder) Size(CREF(ST::Vector2<>) size) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return Size(ST::Vector2{
            static_cast<int>(size.x),
            static_cast<int>(size.y)
          });
        }
        REF(WindowConfigBuilder) Size(const int width, const int height) {
          return Size(ST::Vector2{width, height});
        }
        REF(WindowConfigBuilder) Size(const float width, const float height) {
          return Size(ST::Vector2{width, height});
        }

        REF(WindowConfigBuilder) MinimalSize(CREF(ST::Vector2<int>) size) {
          build_object.min_size_vec2 = size;
          return *this;
        }
        REF(WindowConfigBuilder) MinimalSize(CREF(ST::Vector2<>) size) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return MinimalSize(ST::Vector2{
            static_cast<int>(size.x),
            static_cast<int>(size.y)
          });
        }
        REF(WindowConfigBuilder) MinimalSize(const int width, const int height) {
          return MinimalSize(ST::Vector2{width, height});
        }
        REF(WindowConfigBuilder) MinimalSize(const float width, const float height) {
          return MinimalSize(ST::Vector2{width, height});
        }

        REF(WindowConfigBuilder) MaximumSize(CREF(ST::Vector2<int>) size) {
          build_object.max_size_vec2 = size;
          return *this;
        }
        REF(WindowConfigBuilder) MaximumSize(CREF(ST::Vector2<>) size) {
          Logger::Warning("Clipping floats to ints. Be careful!");
          return MaximumSize(ST::Vector2{
            static_cast<int>(size.x),
            static_cast<int>(size.y)
          });
        }
        REF(WindowConfigBuilder) MaximumSize(const int width, const int height) {
          return MaximumSize(ST::Vector2{width, height});
        }
        REF(WindowConfigBuilder) MaximumSize(const float width, const float height) {
          return MaximumSize(ST::Vector2{width, height});
        }

        REF(WindowConfigBuilder) Opacity(const float opacity) {
          build_object.opacity_float = opacity;
          return *this;
        }

        REF(WindowConfigBuilder) NoVsync() {
          build_object.vsync_bool = false;
          return *this;
        }

        REF(WindowConfigBuilder) EnableImGui(CREF(ImguiConfig) config) {
          build_object.imgui_config = config;
          return *this;
        }
      };
    }
  }
}
