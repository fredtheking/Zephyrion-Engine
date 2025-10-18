#include "Window.hpp"
#include "Logger.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"

void CE::Window::Internal_SetWindowPosition() const {
  ST::Vector2<int> pos;
  switch (p_Config->GetPositionMode()) {
    case Enums::WindowPosition::Centered:
      pos = {SDL_WINDOWPOS_CENTERED};
      break;
    case Enums::WindowPosition::TopLeft:
      pos = {};
      break;
    case Enums::WindowPosition::Custom:
      pos = p_Config->GetPosition();
      break;
  }
  SDL_SetWindowPosition(p_Window, pos.x, pos.y);
}
SDL_WindowFlags CE::Window::Internal_InitialiseFlags() const {
  SDL_WindowFlags flags = SDL_WINDOW_OPENGL;

  if (p_Config->GetOpacity() < 1.0f)
    flags |= SDL_WINDOW_TRANSPARENT;
  if (p_Config->resizable_bool)
    flags |= SDL_WINDOW_RESIZABLE;
  if (p_Config->fullscreen_bool)
    flags |= SDL_WINDOW_FULLSCREEN;
  if (p_Config->borderless_bool)
    flags |= SDL_WINDOW_BORDERLESS;

  switch (p_Config->renderer_enum) {
    case Enums::BackendRenderer::OpenGL:
      flags |= SDL_WINDOW_OPENGL; break;
    case Enums::BackendRenderer::Vulkan:
      flags |= SDL_WINDOW_VULKAN; break;
    case Enums::BackendRenderer::Metal:
      flags |= SDL_WINDOW_METAL; break;
  }

  return flags;
}


void CE::Window::UpdateIcon(CREF(std::string) filepath) {
  p_Icon = Helpers::Loaders::PNGtoSurface(filepath);
  ASSERT(p_Icon, Error, "Failed loading icon", "Loaded icon", SDL_SetWindowIcon(p_Window, p_Icon);)
}

CE::Window::Window(CREF(SPTR(Configs::WindowConfig)) window_config) {
  p_Config = window_config;
  Logger::Information("Creating window...");

  p_Window = SDL_CreateWindow(
    p_Config->GetTitle().c_str(),
    p_Config->GetSize().x,
    p_Config->GetSize().y,
    Internal_InitialiseFlags()
  );
  ASSERT_SDL(p_Window, "Failed initialising Window", "",
    Internal_SetWindowPosition();
  );

  p_Renderer = SDL_CreateRenderer(p_Window, nullptr);
  ASSERT_SDL(p_Renderer, "Failed initialising Renderer for window", "");

  UpdateIcon("assets/engine/icon.png");
  Logger::DebugLog("Current Flags: " + Helpers::Enums::ToString(SDL_GetWindowFlags(p_Window)));

  Logger::Information("Finished creating window");
}

CE::Window::~Window() {
  Logger::Information("Destroying window...");

  ASSERT(p_Renderer, Error, "Failed destroying Renderer", "Destroyed Renderer", SDL_DestroyRenderer(p_Renderer))
  ASSERT(p_Window, Error, "Failed destroying Window", "Destroyed Window", SDL_DestroyWindow(p_Window))

  Logger::Information("Finished destroying window");
}

