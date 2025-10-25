#include "ImguiHandler.hpp"
#include "Window.hpp"
#include "Logger.hpp"

void ZE::ImguiHandler::Render() const {
  if (p_Config.process_event) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();
    p_Config.process_event();

    ImGui::Render();
    if (GET_IO_SINGLETON.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(p_MainWindow.p_Window, p_MainWindow.m_GLContext);
    }
  }
}

void ZE::ImguiHandler::Draw() const {
  if (p_Config.process_event)
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ZE::ImguiHandler::ImguiHandler(CREF(Window) window)
: p_Config(window.p_Config.imgui_config.value())
, p_MainWindow(window){
  Logger::Information("Creating imgui handler...");

  const float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  DEFINE_IO_VARIABLE
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.IniFilename = nullptr;

  if (p_Config.dark_theme) ImGui::StyleColorsDark();
  else                     ImGui::StyleColorsLight();

  REF(ImGuiStyle) style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;

  ImGui_ImplSDL3_InitForOpenGL(window.p_Window, window.m_GLContext);
  ImGui_ImplOpenGL3_Init();

  Logger::Information("Finished creating imgui handler");
}
ZE::ImguiHandler::~ImguiHandler() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}
