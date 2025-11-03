#include "App.hpp"

#include "core/Input.hpp"
#include "core/Logger.hpp"
#include "utils/Util.hpp"

namespace ZE {
  void App::Initialise() {
    Logger::Separator(Colors::Yellow, "Registration ended. Doing final touches...");

    //TODO: come up with smth here

    Logger::Separator(Colors::Lime, "Everything set up. Starting runtime process");
  }
  void App::Terminate() {
    p_MainWindow.reset();
    SDL_Quit();

    Logger::Separator(Colors::Lime, "Goodbye world");
  }

  void App::Create(CREF(Configs::WindowConfig) window_config) {
    Logger::Separator(Colors::SkyBlue, "Hello world! Setting up engine...");

    Util::AssertSDL(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), "Failed initialising SDL3", "Initialised SDL3", true);

    p_MainWindow = MAKE_UPTR(Window)(window_config);
    m_Windows.push_back(p_MainWindow);

    Util::AssertSDL(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)), "Failed initialising GLAD", "", true);
    CREF(ST::Color) bg_color = Colors::BrightBlack;
    glClearColor(bg_color.rgba_float.red, bg_color.rgba_float.green, bg_color.rgba_float.blue, 1);

    p_Config = MAKE_UPTR(Configs::AppConfig)(
      p_MainWindow->p_Config
    );
    Logger::Separator(Colors::Orange, "Engine set up. Starting custom registration...");
  }
  void App::Run() {
    Initialise();

    while (m_Running) {
      PollInput();
      Process();
      Render();
    }

    Logger::Separator(Colors::Orange, "Terminating app...");
  }

  void App::PollInput() {
    Input::ProcessEvent(m_Event);

    m_Running = !Input::QuitRequested();
    if (Input::IsKeyPressed(Enums::ZE_Keys::Escape))
      m_Running = false;
  }
  void App::Process() {
    m_ProcessDeltatime = Util::Process::GetDeltaTime();

    for (CREF(WPTR(Window)) window: m_Windows) {
      if (const auto ptr = window.lock())
        ptr->Process();
    }
  }
  void App::Render() {
    m_RenderDeltatime = Util::Render::GetDeltaTime();

    for (CREF(WPTR(Window)) window: m_Windows) {
      if (const auto ptr = window.lock())
        ptr->Render();
    }
  }
}