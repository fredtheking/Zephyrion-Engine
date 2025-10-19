#include "App.hpp"

#include "core/Logger.hpp"

void CE::App::Initialise() {
  Logger::Separator(Colors::Yellow, "Registration ended. Initialising custom stuff...");

  //TODO: come up with smth here

  Logger::Separator(Colors::Lime, "Everything set up. Starting runtime process");
}
void CE::App::Terminate() {
  Logger::Separator(Colors::Orange, "Terminating app...");

  p_MainWindow.reset();
  SDL_Quit();

  Logger::Separator(Colors::Lime, "Goodbye world");
}

void CE::App::Setup(CREF(Configs::WindowConfig) window_config) {
  p_Config = MAKE_UPTR(Configs::AppConfig)(
    MAKE_SPTR(Configs::WindowConfig)(window_config)
  );


  Logger::Separator(Colors::SkyBlue, "Hello, world! Setting up engine...");

  ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), Critical, "Failed initialising SDL3", "Initialised SDL3")
  p_MainWindow = MAKE_UPTR(Window)(p_Config->window);

  Logger::Separator(Colors::Orange, "Engine set up. Starting custom registration...");
}
void CE::App::Run() {
  Initialise();

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
