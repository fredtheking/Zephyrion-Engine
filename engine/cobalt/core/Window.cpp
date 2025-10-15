#include "Window.hpp"
#include "Logger.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"

void CE::Window::UpdateIcon(CREF(std::string) filepath) {
  p_Icon = Helpers::Loaders::PNGtoSurface(filepath);
  ASSERT(p_Icon, Error, "Failed loading icon", "Loaded icon", SDL_SetWindowIcon(p_Window, p_Icon);)
}

CE::Window::Window(CREF(SPTR(Configs::WindowConfig)) window_config) {
  p_Config = window_config;
  Logger::Information("Creating window...");

  p_Window = SDL_CreateWindow(
    p_Config->title_str.c_str(),
    p_Config->size_vec2.x,
    p_Config->size_vec2.y,
    p_Config->flags_enums
  );
  ASSERT_SDL(p_Window, "Failed initialising Window", "", p_Config->window = p_Window);

  p_Renderer = SDL_CreateRenderer(p_Window, nullptr);
  ASSERT_SDL(p_Renderer, "Failed initialising Renderer for window", "");

  UpdateIcon("assets/engine/icon.png");

  Logger::Information("Finished creating window");
}

CE::Window::~Window() {
  Logger::Information("Destroying window...");

  ASSERT(p_Renderer, Error, "Failed destroying Renderer", "Destroyed Renderer", SDL_DestroyRenderer(p_Renderer))
  ASSERT(p_Window, Error, "Failed destroying Window", "Destroyed Window", SDL_DestroyWindow(p_Window))

  Logger::Information("Finished destroying window");
}

