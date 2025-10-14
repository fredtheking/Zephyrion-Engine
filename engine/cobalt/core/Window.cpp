#include "Window.hpp"

CE::Window::Window(int width, int height, const std::string &title, SDL_WindowFlags flags) {
  p_Window = SDL_CreateWindow(title.c_str(), width, height, flags);
  CRASH_ASSERT(p_Window, fprintf(stderr, "Failed initialising Window: %s", SDL_GetError()))

  p_Renderer = SDL_CreateRenderer(p_Window, nullptr);
  CRASH_ASSERT(p_Renderer, fprintf(stderr, "Failed initialising Renderer: %s", SDL_GetError()))
}

CE::Window::~Window() {
  if (p_Window) SDL_DestroyWindow(p_Window);
  if (p_Renderer) SDL_DestroyRenderer(p_Renderer);
}

