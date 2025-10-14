#include "App.hpp"

void CE::App::Setup() {
  CRASH_ASSERT(
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
    fprintf(stderr, "Failed initialising SDL3: %s", SDL_GetError())
  )

  p_MainWindow = MAKE_UPTR(Window)(1920, 1080, "Hello, Cobalt!", 0);
}
void CE::App::Terminate() {
  p_MainWindow.reset();

  SDL_Quit();
}


void CE::App::Run() {
  Setup();

  while (m_Running) {
    Process();
    Render();
  }

  Terminate();
}

void CE::App::Process() {
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
void CE::App::Render() {
  SDL_SetRenderDrawColor(p_MainWindow->p_Renderer, 0, 64, 92, 255);
  SDL_RenderClear(p_MainWindow->p_Renderer);
  SDL_RenderPresent(p_MainWindow->p_Renderer);
}