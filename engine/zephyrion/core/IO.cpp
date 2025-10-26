#include "IO.hpp"
#include "Logger.hpp"
#define CAST_KEY(X) static_cast<UINT16>(X)
#define CAST_MOUSE(X) static_cast<UINT8>(X)


std::array<bool, ZE::IO::MAX_KEYS> ZE::IO::s_CurrentKeys{};
std::array<bool, ZE::IO::MAX_KEYS> ZE::IO::s_PreviousKeys{};
std::array<bool, ZE::IO::MAX_BUTTONS> ZE::IO::s_CurrentMouse{};
std::array<bool, ZE::IO::MAX_BUTTONS> ZE::IO::s_PreviousMouse{};
ST_VEC2() ZE::IO::s_MousePos{};
ST_VEC2() ZE::IO::s_MouseWheel{};
bool ZE::IO::s_Quit = false;
STR ZE::IO::s_TextInput{};
VEC(STR) ZE::IO::s_DropFiles{};
VEC(SDL_Event) ZE::IO::s_WindowEvents{};
std::unordered_map<SDL_JoystickID, ZE::Low::GamepadState> ZE::IO::s_Gamepads{};


void ZE::IO::ProcessEvent(REF(SDL_Event) e) {
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
      case SDL_EVENT_WINDOW_RESIZED:
      case SDL_EVENT_WINDOW_MINIMIZED:
      case SDL_EVENT_WINDOW_RESTORED:
      case SDL_EVENT_WINDOW_FOCUS_GAINED:
      case SDL_EVENT_WINDOW_FOCUS_LOST:
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

void ZE::IO::OpenGamepad(const SDL_JoystickID id) {
  if (s_Gamepads.contains(id)) {
    Logger::Warning("Gamepad with this ID already exists!");
    return;
  }
  if (SDL_OpenGamepad(id)) s_Gamepads[id] = Low::GamepadState{};
}
void ZE::IO::CloseGamepad(const SDL_JoystickID id) {
  if (const auto it = s_Gamepads.find(id); it != s_Gamepads.end()) {
    if (SDL_Gamepad* pad = SDL_OpenGamepad(id)) SDL_CloseGamepad(pad);
    s_Gamepads.erase(it);
  }
}
const ZE::Low::GamepadState* ZE::IO::GetGamepad(const SDL_JoystickID id) {
  const auto it = s_Gamepads.find(id);
  return it != s_Gamepads.end() ? &it->second : nullptr;
}

bool ZE::IO::QuitRequested() {
  return s_Quit;
}

bool ZE::IO::IsKeyDown(Enums::ZE_Keys key) {
  return s_CurrentKeys[CAST_KEY(key)];
}
bool ZE::IO::IsKeyPressed(Enums::ZE_Keys key) {
  UINT16 int_key = CAST_KEY(key);
  return s_CurrentKeys[int_key] && !s_PreviousKeys[int_key];
}
bool ZE::IO::IsKeyReleased(Enums::ZE_Keys key) {
  UINT16 int_key = CAST_KEY(key);
  return !s_CurrentKeys[int_key] && s_PreviousKeys[int_key];
}

bool ZE::IO::IsMouseDown(Enums::ZE_Mouse button) {
  return s_CurrentMouse[CAST_MOUSE(button)];
}
bool ZE::IO::IsMousePressed(Enums::ZE_Mouse button) {
  UINT8 int_button = CAST_MOUSE(button);
  return s_CurrentMouse[int_button] && !s_PreviousMouse[int_button];
}
bool ZE::IO::IsMouseReleased(Enums::ZE_Mouse button) {
  UINT8 int_button = CAST_MOUSE(button);
  return !s_CurrentMouse[int_button] && s_PreviousMouse[int_button];
}

ZE::ST::Vector2<> ZE::IO::MousePosition() {
  return s_MousePos;
}
float ZE::IO::MousePositionX() {
  return s_MousePos.x;
}
float ZE::IO::MousePositionY() {
  return s_MousePos.y;
}

ZE::ST::Vector2<> ZE::IO::MouseWheel() {
  return s_MouseWheel;
}
float ZE::IO::MouseWheelX() {
  return s_MouseWheel.x;
}
float ZE::IO::MouseWheelY() {
  return s_MouseWheel.y;
}

const std::string & ZE::IO::GetTextInput() {
  return s_TextInput;
}
const std::vector<std::string> & ZE::IO::GetDroppedFiles() {
  return s_DropFiles;
}
const std::vector<SDL_Event> & ZE::IO::GetWindowEvents() {
  return s_WindowEvents;
}

