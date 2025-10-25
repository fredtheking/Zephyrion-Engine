#include "App.hpp"

#include "core/IO.hpp"
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

void ZE::App::Setup(CREF(Configs::WindowConfig) window_config) {
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

  while (m_Running) {
    PollInput();
    Process();
    Render();
  }

  Logger::Separator(Colors::Orange, "Terminating app...");
}

void ZE::App::PollInput() {
  IO::ProcessEvent(m_Event);
  m_Running = !IO::QuitRequested();
}
void ZE::App::Process() {
  m_ProcessDeltatime = Util::Process::GetDeltaTime();

  if (IO::IsKeyPressed(Enums::ZE_Keys::Escape))
    m_Running = false;
}
void ZE::App::Render() {
  m_RenderDeltatime = Util::Render::GetDeltaTime();
  if (p_MainWindow->m_Imgui) DEFINE_IO_VARIABLE

  if (p_MainWindow->m_Imgui) p_MainWindow->m_Imgui.value()->Render();
  glViewport(0, 0, p_Config->window->GetSize().x, p_Config->window->GetSize().y);
  glClear(GL_COLOR_BUFFER_BIT);
  if (p_MainWindow->m_Imgui) p_MainWindow->m_Imgui.value()->Draw();
  SDL_GL_SwapWindow(p_MainWindow->p_Window);
}
