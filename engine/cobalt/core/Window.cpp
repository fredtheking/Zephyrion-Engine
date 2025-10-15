#include "Window.hpp"
#include "Logger.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"

void CE::Window::UpdateIcon(CREF(std::string) filepath) {
  p_Icon = Helpers::Loaders::PNGtoSurface(filepath);
  ASSERT(p_Icon, Error, "Failed loading icon", "Loaded icon", SDL_SetWindowIcon(p_Window, p_Icon);)
}

CE::Window::Window(const int width, const int height, CREF(std::string) title, const SDL_WindowFlags flags) {
  Logger::Information("Creating window...");

  p_Window = SDL_CreateWindow(title.c_str(), width, height, flags);
  ASSERT_SDL(p_Window, "Failed initialising Window", "Initialised Window");

  p_Renderer = SDL_CreateRenderer(p_Window, nullptr);
  ASSERT_SDL(p_Renderer, "Failed initialising Renderer for window", "Initialised Renderer for window");

  UpdateIcon("assets/engine/icon.png");

  Logger::Information("Finished creating window");
}

CE::Window::~Window() {
  Logger::Information("Destroying window...");

  if (p_Renderer) {
    SDL_DestroyRenderer(p_Renderer);
    Logger::Success("Destroyed Renderer");
  }
  if (p_Window) {
    SDL_DestroyWindow(p_Window);
    Logger::Success("Destroyed Window");
  }

  Logger::Information("Finished destroying window");
}

