#include "ImguiHandler.hpp"

void ZE::ImguiHandler::Render() const {
  if (p_Config.process_event) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    p_Config.process_event();

    ImGui::EndFrame();
    ImGui::Render();
  }
}

void ZE::ImguiHandler::Draw() const {
  if (p_Config.process_event)
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ZE::ImguiHandler::ImguiHandler(REF(Configs::ImguiConfig) imgui_config, CREF(Window) window)
: p_Config(imgui_config)
, p_MainWindow(window) {
  Logger::Information("Creating imgui handler...");

  const float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  DEFINE_IO_VARIABLE
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
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
