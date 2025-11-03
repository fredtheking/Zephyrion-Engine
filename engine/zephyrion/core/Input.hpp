#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/simple_types/Vector2.hpp"
#include "zephyrion/utils/Enums.hpp"

namespace ZE {
  namespace Low {
    struct GamepadState {
      std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> buttons{};
      std::array<float, SDL_GAMEPAD_AXIS_COUNT> axes{};
    };
  }

  class Input {
  private:
    static void ProcessEvent(REF(SDL_Event) e);
  public:
    static void OpenGamepad(SDL_JoystickID id);
    static void CloseGamepad(SDL_JoystickID id);
    [[nodiscard]] static const Low::GamepadState* GetGamepad(SDL_JoystickID id);

    [[nodiscard]] static bool QuitRequested();

    [[nodiscard]] static bool IsKeyDown(Enums::ZE_Keys key);
    [[nodiscard]] static bool IsKeyPressed(Enums::ZE_Keys key);
    [[nodiscard]] static bool IsKeyReleased(Enums::ZE_Keys key);

    [[nodiscard]] static bool IsMouseDown(Enums::ZE_Mouse button);
    [[nodiscard]] static bool IsMousePressed(Enums::ZE_Mouse button);
    [[nodiscard]] static bool IsMouseReleased(Enums::ZE_Mouse button);

    [[nodiscard]] static ST::Vector2<> MousePosition();
    [[nodiscard]] static float MousePositionX();
    [[nodiscard]] static float MousePositionY();
    [[nodiscard]] static ST::Vector2<> MouseWheel();
    [[nodiscard]] static float MouseWheelX();
    [[nodiscard]] static float MouseWheelY();

    [[nodiscard]] static const REF(STR) GetTextInput();
    [[nodiscard]] static const REF(VEC(STR)) GetDroppedFiles();
    [[nodiscard]] static const REF(VEC(SDL_Event)) GetWindowEvents();

  private:
    static constexpr int MAX_KEYS = SDL_SCANCODE_COUNT;
    static constexpr int MAX_BUTTONS = 5;

    static std::array<bool, MAX_KEYS> s_CurrentKeys;
    static std::array<bool, MAX_KEYS> s_PreviousKeys;
    static std::array<bool, MAX_BUTTONS> s_CurrentMouse;
    static std::array<bool, MAX_BUTTONS> s_PreviousMouse;

    static ST::Vector2<> s_MousePos;
    static ST::Vector2<> s_MouseWheel;
    static bool s_Quit;

    static STR s_TextInput;
    static VEC(STR) s_DropFiles;
    static VEC(SDL_Event) s_WindowEvents;

    static std::unordered_map<SDL_JoystickID, Low::GamepadState> s_Gamepads;
  public:
    //...

  private:
    friend class App;
  public:
    STATIC_ONLY_CONSTRUCTOR(Input)
  };
}
