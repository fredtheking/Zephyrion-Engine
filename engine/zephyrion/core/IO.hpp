#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/simple_types/Vector2.hpp"

namespace ZE {
  namespace Low {
    struct GamepadState {
      std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> buttons{};
      std::array<float, SDL_GAMEPAD_AXIS_COUNT> axes{};
    };
  }

  class IO {
  private:
    //...
  public:
    void OpenGamepad(SDL_JoystickID id);
    void CloseGamepad(SDL_JoystickID id);
    [[nodiscard]] const Low::GamepadState* GetGamepad(SDL_JoystickID id) const;

    [[nodiscard]] bool QuitRequested() const;

    [[nodiscard]] bool IsKeyDown(SDL_Scancode key) const;
    [[nodiscard]] bool IsKeyPressed(SDL_Scancode key) const;
    [[nodiscard]] bool IsKeyReleased(SDL_Scancode key) const;

    [[nodiscard]] bool IsMouseDown(UINT8 button) const;
    [[nodiscard]] bool IsMousePressed(UINT8 button) const;
    [[nodiscard]] bool IsMouseReleased(UINT8 button) const;

    [[nodiscard]] ST::Vector2<int> MousePosition() const;
    [[nodiscard]] int MousePositionX() const;
    [[nodiscard]] int MousePositionY() const;
    [[nodiscard]] ST::Vector2<> MouseWheel() const;
    [[nodiscard]] float MouseWheelX() const;
    [[nodiscard]] float MouseWheelY() const;

    [[nodiscard]] const REF(STR) GetTextInput() const;
    [[nodiscard]] const REF(VEC(STR)) GetDroppedFiles() const;
    [[nodiscard]] const REF(VEC(SDL_Event)) GetWindowEvents() const;

  private:
    static constexpr int MAX_KEYS = SDL_SCANCODE_COUNT;
    static constexpr int MAX_BUTTONS = 8;

    std::array<bool, MAX_KEYS> m_CurrentKeys{};
    std::array<bool, MAX_KEYS> m_PreviousKeys{};
    std::array<bool, MAX_BUTTONS> m_CurrentMouse{};
    std::array<bool, MAX_BUTTONS> m_PreviousMouse{};

    ST::Vector2<int> m_MousePos;
    ST::Vector2<> m_MouseWheel;
    bool m_Quit = false;

    STR m_TextInput;
    VEC(STR) m_DropFiles;
    VEC(SDL_Event) m_WindowEvents;

    std::unordered_map<SDL_JoystickID, Low::GamepadState> m_Gamepads;
  public:
    //...

  private:
    //...
  public:
    //...
  };
}
