#include "ImguiHandler.hpp"

void ZE::ImguiHandler::Render() const {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  if (p_Config.process_event) p_Config.process_event();

  ImGui::Render();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  SDL_SetRenderScale(p_MainWindow.p_Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), p_MainWindow.p_Renderer);
}

ZE::ImguiHandler::ImguiHandler(REF(Configs::ImguiConfig) imgui_config, CREF(Window) window)
: p_Config(imgui_config)
, p_MainWindow(window) {
  Logger::Information("Creating imgui handler...");

  const float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  if (p_Config.dark_theme) ImGui::StyleColorsDark();
  else                     ImGui::StyleColorsLight();

  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;

  ImGui_ImplSDL3_InitForSDLRenderer(window.p_Window, window.p_Renderer);
  ImGui_ImplSDLRenderer3_Init(window.p_Renderer);

  Logger::Information("Finished creating imgui handler");
}
ZE::ImguiHandler::~ImguiHandler() {
  //...
}
