#include "App.hpp"

#include "core/Logger.hpp"

void CE::App::Setup() {
  Logger::Separator(Colors::Yellow, "Hello, world! Setting up engine...");

  ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), Critical, "Failed initialising SDL3", "Initialised SDL3")
  p_MainWindow = MAKE_UPTR(Window)(1920, 1080, "Hello, Cobalt!", 0);

  Logger::Separator(Colors::Lime, "Engine set up. Starting runtime");
}
void CE::App::Terminate() {
  Logger::Separator(Colors::Red, "Terminating app...");

  p_MainWindow.reset();

  SDL_Quit();

  Logger::Separator(Colors::Lime, "Goodbye");
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
void CE::App::Render() const {
  SDL_SetRenderDrawColor(p_MainWindow->p_Renderer, 0, 64, 92, 255);
  SDL_RenderClear(p_MainWindow->p_Renderer);
  SDL_RenderPresent(p_MainWindow->p_Renderer);
}
