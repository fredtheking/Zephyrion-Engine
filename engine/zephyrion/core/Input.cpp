#include "Input.hpp"
#include "Logger.hpp"
#define CAST_KEY(X) static_cast<UINT16>(X)
#define CAST_MOUSE(X) static_cast<UINT8>(X)


std::array<bool, ZE::Input::MAX_KEYS> ZE::Input::s_CurrentKeys{};
std::array<bool, ZE::Input::MAX_KEYS> ZE::Input::s_PreviousKeys{};
std::array<bool, ZE::Input::MAX_BUTTONS> ZE::Input::s_CurrentMouse{};
std::array<bool, ZE::Input::MAX_BUTTONS> ZE::Input::s_PreviousMouse{};
ST_VEC2() ZE::Input::s_MousePos{};
ST_VEC2() ZE::Input::s_MouseWheel{};
bool ZE::Input::s_Quit = false;
STR ZE::Input::s_TextInput{};
VEC(STR) ZE::Input::s_DropFiles{};
VEC(SDL_Event) ZE::Input::s_WindowEvents{};
std::unordered_map<SDL_JoystickID, ZE::Low::GamepadState> ZE::Input::s_Gamepads{};


void ZE::Input::ProcessEvent(REF(SDL_Event) e) {
  s_PreviousKeys = s_CurrentKeys;
  s_PreviousMouse = s_CurrentMouse;
  s_MouseWheel.x = s_MouseWheel.y = 0;
  s_TextInput.clear();
  s_DropFiles.clear();
  s_WindowEvents.clear();

  while (SDL_PollEvent(&e)) {
    if (ImGui::GetCurrentContext()) ImGui_ImplSDL3_ProcessEvent(&e);
    switch (e.type) {
      // ===================== SYSTEM =====================
      case SDL_EVENT_QUIT:
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        s_Quit = true;
        break;

        // ===================== KEYBOARD =====================
      case SDL_EVENT_KEY_DOWN:
        if (e.key.scancode < MAX_KEYS)
          s_CurrentKeys[e.key.scancode] = true;
        break;
      case SDL_EVENT_KEY_UP:
        if (e.key.scancode < MAX_KEYS)
          s_CurrentKeys[e.key.scancode] = false;
        break;
      case SDL_EVENT_TEXT_INPUT:
        s_TextInput += e.text.text;
        break;

        // ===================== MOUSE =====================
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (e.button.button < MAX_BUTTONS)
          s_CurrentMouse[e.button.button] = true;
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        if (e.button.button < MAX_BUTTONS)
          s_CurrentMouse[e.button.button] = false;
        break;
      case SDL_EVENT_MOUSE_MOTION:
        s_MousePos.x = e.motion.x;
        s_MousePos.y = e.motion.y;
        break;
      case SDL_EVENT_MOUSE_WHEEL:
        s_MouseWheel.x = e.wheel.x;
        s_MouseWheel.y = e.wheel.y;
        break;

        // ===================== WINDOW =====================
      case SDL_EVENT_WINDOW_SHOWN:
      case SDL_EVENT_WINDOW_HIDDEN:
      case SDL_EVENT_WINDOW_EXPOSED:
      case SDL_EVENT_WINDOW_MOVED:
      case SDL_EVENT_WINDOW_RESIZED:
      case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
      case SDL_EVENT_WINDOW_MINIMIZED:
      case SDL_EVENT_WINDOW_MAXIMIZED:
      case SDL_EVENT_WINDOW_RESTORED:
      case SDL_EVENT_WINDOW_MOUSE_ENTER:
      case SDL_EVENT_WINDOW_MOUSE_LEAVE:
      case SDL_EVENT_WINDOW_FOCUS_GAINED:
      case SDL_EVENT_WINDOW_FOCUS_LOST:
      case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
      case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
      case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
      case SDL_EVENT_WINDOW_DESTROYED:
        s_WindowEvents.push_back(e);
        break;

        // ===================== DROP =====================
      case SDL_EVENT_DROP_FILE:
        if (e.drop.data)
          s_DropFiles.emplace_back(e.drop.data);
        break;

        // ===================== GAMEPAD =====================
      case SDL_EVENT_GAMEPAD_ADDED:
        OpenGamepad(e.gdevice.which);
        break;
      case SDL_EVENT_GAMEPAD_REMOVED:
        CloseGamepad(e.gdevice.which);
        break;
      case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        s_Gamepads[e.gbutton.which].buttons[e.gbutton.button] = true;
        break;
      case SDL_EVENT_GAMEPAD_BUTTON_UP:
        s_Gamepads[e.gbutton.which].buttons[e.gbutton.button] = false;
        break;
      case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        s_Gamepads[e.gaxis.which].axes[e.gaxis.axis] = e.gaxis.value / 32767.0f;
        break;
      default:
        Logger::Warning("Some event had been unhandled: " + std::to_string(e.type));
        break;
    }
  }
}

void ZE::Input::OpenGamepad(const SDL_JoystickID id) {
  if (s_Gamepads.contains(id)) {
    Logger::Warning("Gamepad with this ID already exists!");
    return;
  }
  if (SDL_OpenGamepad(id)) s_Gamepads[id] = Low::GamepadState{};
}
void ZE::Input::CloseGamepad(const SDL_JoystickID id) {
  if (const auto it = s_Gamepads.find(id); it != s_Gamepads.end()) {
    if (SDL_Gamepad* pad = SDL_OpenGamepad(id)) SDL_CloseGamepad(pad);
    s_Gamepads.erase(it);
  }
}
const ZE::Low::GamepadState* ZE::Input::GetGamepad(const SDL_JoystickID id) {
  const auto it = s_Gamepads.find(id);
  return it != s_Gamepads.end() ? &it->second : nullptr;
}

bool ZE::Input::QuitRequested() {
  return s_Quit;
}

bool ZE::Input::IsKeyDown(Enums::ZE_Keys key) {
  return s_CurrentKeys[CAST_KEY(key)];
}
bool ZE::Input::IsKeyPressed(Enums::ZE_Keys key) {
  const auto int_key = CAST_KEY(key);
  return s_CurrentKeys[int_key] && !s_PreviousKeys[int_key];
}
bool ZE::Input::IsKeyReleased(Enums::ZE_Keys key) {
  const auto int_key = CAST_KEY(key);
  return !s_CurrentKeys[int_key] && s_PreviousKeys[int_key];
}

bool ZE::Input::IsMouseDown(Enums::ZE_Mouse button) {
  return s_CurrentMouse[CAST_MOUSE(button)];
}
bool ZE::Input::IsMousePressed(Enums::ZE_Mouse button) {
  const auto int_button = CAST_MOUSE(button);
  return s_CurrentMouse[int_button] && !s_PreviousMouse[int_button];
}
bool ZE::Input::IsMouseReleased(Enums::ZE_Mouse button) {
  const auto int_button = CAST_MOUSE(button);
  return !s_CurrentMouse[int_button] && s_PreviousMouse[int_button];
}

ZE::ST::Vector2<> ZE::Input::MousePosition() {
  return s_MousePos;
}
float ZE::Input::MousePositionX() {
  return s_MousePos.x;
}
float ZE::Input::MousePositionY() {
  return s_MousePos.y;
}

ZE::ST::Vector2<> ZE::Input::MouseWheel() {
  return s_MouseWheel;
}
float ZE::Input::MouseWheelX() {
  return s_MouseWheel.x;
}
float ZE::Input::MouseWheelY() {
  return s_MouseWheel.y;
}

CREF(STR) ZE::Input::GetTextInput() {
  return s_TextInput;
}
CREF(VEC(STR)) ZE::Input::GetDroppedFiles() {
  return s_DropFiles;
}
CREF(VEC(SDL_Event)) ZE::Input::GetWindowEvents() {
  return s_WindowEvents;
}

