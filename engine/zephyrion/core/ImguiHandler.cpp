#include "ImguiHandler.hpp"
#include "Window.hpp"
#include "Logger.hpp"


void SetupImGuiStyle()
{
	// Fork of Classic Steam style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.25882354f, 0.3019103f, 0.3372549f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.25882354f, 0.30796936f, 0.3372549f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20000002f, 0.24177396f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.50980395f, 0.5345452f, 0.5686275f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.15612736f, 0.19641457f, 0.22317594f, 0.52f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20000002f, 0.2383405f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22745098f, 0.25532272f, 0.29803923f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25882354f, 0.28979215f, 0.3372549f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20000002f, 0.24005724f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25882354f, 0.31402847f, 0.3372549f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20000002f, 0.25035766f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.30980393f, 0.38426325f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.23921569f, 0.2964403f, 0.31764707f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.21960784f, 0.27885213f, 0.29803923f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20784314f, 0.2507616f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5882353f, 0.17647056f, 0.4309518f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.30980393f, 0.3701254f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.50980395f, 0.54666334f, 0.5686275f, 0.5f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25882354f, 0.31200877f, 0.3372549f, 0.4f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30980393f, 0.39274594f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.30980393f, 0.3899184f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30980393f, 0.37295297f, 0.41960785f, 0.6f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.50980395f, 0.53151566f, 0.5686275f, 0.5f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.301166f, 0.37557152f, 0.46781117f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5793991f, 0.2635893f, 0.36931103f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.22958612f, 0.2826547f, 0.32618028f, 0.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.50980395f, 0.54969287f, 0.5686275f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.5882353f, 0.17647056f, 0.40974522f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.30980393f, 0.39557353f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.50980395f, 0.54969287f, 0.5686275f, 0.78f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.5882353f, 0.17647056f, 0.29310778f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.20000002f, 0.23490702f, 0.26666668f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.41960785f, 0.30980393f, 0.3691829f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.5882353f, 0.17647056f, 0.4415552f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.27843142f, 0.81728536f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.8240347f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5882353f, 0.17647056f, 0.515779f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.7294118f, 0.23921569f, 0.5674157f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.5882353f, 0.17647056f, 0.37793496f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}


void ZE::ImguiHandler::Render() const {
  if (p_Config.process_event) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (p_Config.docking_bool) ImGui::DockSpaceOverViewport();
    p_Config.process_event();

    ImGui::Render();
    if (p_Config.floating_window_bool)
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
: p_Config(window.p_Config->imgui_config.value())
, p_MainWindow(window){
  Logger::Information("Creating imgui handler...");

  const float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  DEFINE_IO_VARIABLE
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	if (p_Config.floating_window_bool)
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	if (p_Config.docking_bool)
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.IniFilename = nullptr;

  if (p_Config.dark_theme_bool) ImGui::StyleColorsDark();
  else                     ImGui::StyleColorsLight();

  REF(ImGuiStyle) style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;
	SetupImGuiStyle();

  ImGui_ImplSDL3_InitForOpenGL(window.p_Window, window.m_GLContext);
  ImGui_ImplOpenGL3_Init();

  Logger::Information("Finished creating imgui handler");
}
ZE::ImguiHandler::~ImguiHandler() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}
