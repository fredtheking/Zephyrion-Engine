#include "App.hpp"
#include "core/Logger.hpp"
#include "utils/Util.hpp"

void ZE::App::Initialise() {
  Logger::Separator(Colors::Yellow, "Registration ended. Doing final touches...");

  //TODO: come up with smth here

  Logger::Separator(Colors::Lime, "Everything set up. Starting runtime process");
}
void ZE::App::Terminate() {
  p_MainWindow.reset();
  SDL_Quit();

  Logger::Separator(Colors::Lime, "Goodbye world");
}

void ZE::App::Setup(CREF(Configs::WindowConfig) window_config, CREF(Configs::ImguiConfig) imgui_config) {
  p_Config = MAKE_UPTR(Configs::AppConfig)(
    MAKE_UPTR(Configs::WindowConfig)(window_config)
  );

  Logger::Separator(Colors::SkyBlue, "Hello world! Setting up engine...");

  Util::AssertSDL(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), "Failed initialising SDL3", "Initialised SDL3", true);

  p_MainWindow = MAKE_UPTR(Window)(*p_Config->window);

  Util::AssertSDL(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)), "Failed initialising GLAD", "", true);
  CREF(ST::Color) bg_color = Colors::BrightBlack;
  glClearColor(bg_color.rgba_float.red, bg_color.rgba_float.green, bg_color.rgba_float.blue, 1);

  Logger::Separator(Colors::Orange, "Engine set up. Starting custom registration...");
}
void ZE::App::Run() {
  Initialise();

  // e_ProcessLoop.Start();
  while (m_Running) {
    PollInput();
    Process();
    Render();
  }
  // e_ProcessLoop.Stop();

  Logger::Separator(Colors::Orange, "Terminating app...");
}

void ZE::App::PollInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL3_ProcessEvent(&event);
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
  }
}
void ZE::App::Process() {
  m_ProcessDeltatime = Util::Process::GetDeltaTime();
}
void ZE::App::Render() {
  m_RenderDeltatime = Util::Render::GetDeltaTime();
  DEFINE_IO_VARIABLE

  p_MainWindow->m_Imgui->Render();
  glViewport(0, 0, p_Config->window->GetSize().x, p_Config->window->GetSize().y);
  glClear(GL_COLOR_BUFFER_BIT);
  p_MainWindow->m_Imgui->Draw();
  SDL_GL_SwapWindow(p_MainWindow->p_Window);
}
