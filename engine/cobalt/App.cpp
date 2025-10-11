#include "App.hpp"


void Cobalt::App::Run() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    fprintf(stderr, "Failed initialising SDL3: %s", SDL_GetError());
    std::abort();
  }

  SDL_Window* window = SDL_CreateWindow("Hello, Cobalt!", 1920, 1080, 0);
  if (!window) {
    fprintf(stderr, "Failed creating window: %s", SDL_GetError());
    std::abort();
  }

  SDL_Delay(5000);

  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_Quit();
}

void Cobalt::App::Process() {

}
void Cobalt::App::Render() {

}