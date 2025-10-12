#include "App.hpp"


void Cobalt::App::Run() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    fprintf(stderr, "Failed initialising SDL3: %s", SDL_GetError());
    std::abort();
  }

  m_Window = SDL_CreateWindow("Hello, Cobalt!", 1920, 1080, 0);
  if (!m_Window) {
    fprintf(stderr, "Failed creating Window: %s", SDL_GetError());
    std::abort();
  }

  m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
  if (!m_Renderer) {
    fprintf(stderr, "Failed creating Renderer: %s", SDL_GetError());
    std::abort();
  }


  while (m_Running) {
    Process();
    Render();
  }


  if (m_Renderer) {
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
  }
  if (m_Window) {
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
  }
  SDL_Quit();

  printf("All clean!\n");
}

void Cobalt::App::Process() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        m_Running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_ESCAPE)
          m_Running = false;
      default:
        break;
    }


    if (event.type == SDL_EVENT_QUIT) {
      m_Running = false;
    }
  }
}
void Cobalt::App::Render() {
  SDL_SetRenderDrawColor(m_Renderer, 0, 64, 92, 255);
  SDL_RenderClear(m_Renderer);
  SDL_RenderPresent(m_Renderer);
}