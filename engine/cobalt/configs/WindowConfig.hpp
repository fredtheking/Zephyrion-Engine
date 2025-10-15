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
      SDL_Window* window = nullptr;

      std::string title_str = "Hello, Cobalt Engine!";
      ST::Vector2<int> position_vec2 = NONVALID_VEC2;
      Enums::WindowPosition position_mode_enum = Enums::WindowPosition::Centered;
      ST::Vector2<int> size_vec2 = {800, 600};
      SDL_WindowFlags flags_enums = 0;

      void InternalSetWindowPosition() {
        switch (position_mode_enum) {
          case Enums::WindowPosition::Centered:
            SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            break;
          case Enums::WindowPosition::TopLeft:
            SDL_SetWindowPosition(window, 0, 0);
            break;
          case Enums::WindowPosition::Custom:
            SDL_SetWindowPosition(window, position_vec2.x, position_vec2.y);
            break;
        }
      }
    public:
      GETTER_N_SETTER_DEFAULT(Title, CREF(std::string), title_str)
      GETTER_N_SETTER_DEFAULT(Position, CREF(ST::Vector2<int>), position_vec2,
        position_mode_enum = Enums::WindowPosition::Custom;
        InternalSetWindowPosition();
      )
      GETTER_N_SETTER_DEFAULT(PositionMode, Enums::WindowPosition, position_mode_enum,
        position_vec2 = NONVALID_VEC2;
        InternalSetWindowPosition();
      )
      GETTER_N_SETTER_DEFAULT(Size, CREF(ST::Vector2<int>), size_vec2)
      GETTER_N_SETTER_DEFAULT(Flags, SDL_WindowFlags, flags_enums)
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


        WindowConfig Build() {
          return config;
        }
      };
    }
  }
}


#undef NONVALID_VEC2