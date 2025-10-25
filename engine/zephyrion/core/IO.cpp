#include "IO.hpp"

#include "Logger.hpp"

void ZE::IO::OpenGamepad(const SDL_JoystickID id) {
  if (m_Gamepads.contains(id)) {
    Logger::Warning("Gamepad with this ID already exists!");
    return;
  }
  if (SDL_OpenGamepad(id)) m_Gamepads[id] = Low::GamepadState{};
}
void ZE::IO::CloseGamepad(const SDL_JoystickID id) {
  if (auto it = m_Gamepads.find(id); it != m_Gamepads.end()) {
    if (SDL_Gamepad* pad = SDL_OpenGamepad(id)) SDL_CloseGamepad(pad);
    m_Gamepads.erase(it);
  }
}
const ZE::Low::GamepadState* ZE::IO::GetGamepad(const SDL_JoystickID id) const {
  const auto it = m_Gamepads.find(id);
  return it != m_Gamepads.end() ? &it->second : nullptr;
}
