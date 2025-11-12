#include "ImGuiHandler.hpp"
#include "Window.hpp"
#include "Logger.hpp"
#include "zephyrion/core/renderers/OpenGLHandler.hpp"
#include "zephyrion/core/renderers/VulkanHandler.hpp"
#include "zephyrion/core/renderers/MetalHandler.hpp"


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

namespace ZE {
	template class ImGuiHandler<Renderers::OpenGLHandler>;
	template class ImGuiHandler<Renderers::VulkanHandler>;
	template class ImGuiHandler<Renderers::MetalHandler>;

	template<>
	void ImGuiHandler<Renderers::OpenGLHandler>::Internal_SpecificInit() {
		ImGui_ImplSDL3_InitForOpenGL(
			p_LinkedWindow.p_Window,
			p_LinkedWindow.m_RendererDevice->Get<Renderers::OpenGLHandler>().m_GLContext
		);
		ImGui_ImplOpenGL3_Init();
	}
	template<>
	void ImGuiHandler<Renderers::VulkanHandler>::Internal_SpecificInit() {
		//TODO
	}
	template<>
	void ImGuiHandler<Renderers::MetalHandler>::Internal_SpecificInit() {
		//TODO
	}

	template<>
	void ImGuiHandler<Renderers::OpenGLHandler>::Internal_SpecificShutdown() {
		ImGui_ImplOpenGL3_Shutdown();
	}
	template<>
	void ImGuiHandler<Renderers::VulkanHandler>::Internal_SpecificShutdown() {
		//TODO
	}
	template<>
	void ImGuiHandler<Renderers::MetalHandler>::Internal_SpecificShutdown() {
		//TODO
	}

	template<>
	void ImGuiHandler<Renderers::OpenGLHandler>::Internal_SpecificNewFrame() {
		ImGui_ImplOpenGL3_NewFrame();
	}
	template<>
	void ImGuiHandler<Renderers::VulkanHandler>::Internal_SpecificNewFrame() {
		//TODO
	}
	template<>
	void ImGuiHandler<Renderers::MetalHandler>::Internal_SpecificNewFrame() {
		//TODO
	}

	template<>
	void ImGuiHandler<Renderers::OpenGLHandler>::Internal_SpecificRenderDrawData() {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	template<>
	void ImGuiHandler<Renderers::VulkanHandler>::Internal_SpecificRenderDrawData() {
		//TODO
	}
	template<>
	void ImGuiHandler<Renderers::MetalHandler>::Internal_SpecificRenderDrawData() {
		//TODO
	}

	template<>
	void ImGuiHandler<Renderers::OpenGLHandler>::Internal_SpecificFloatingEndAction() {
		SDL_GL_MakeCurrent(
				p_LinkedWindow.p_Window,
				p_LinkedWindow.m_RendererDevice->Get<Renderers::OpenGLHandler>().m_GLContext
			);
	}
	template<>
	void ImGuiHandler<Renderers::VulkanHandler>::Internal_SpecificFloatingEndAction() {
		//TODO
	}
	template<>
	void ImGuiHandler<Renderers::MetalHandler>::Internal_SpecificFloatingEndAction() {
		//TODO
	}



	template<typename T>
	void ImGuiHandler<T>::Render() const {
		if (p_Config.GetProcessFunc()) {
			Internal_SpecificNewFrame();
			ImGui_ImplSDL3_NewFrame();
			ImGui::NewFrame();

			if (p_Config.GetDocking()) ImGui::DockSpaceOverViewport();
			p_Config.GetProcessFunc()();

			ImGui::Render();
			if (p_Config.GetFloatingWindows())
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				Internal_SpecificFloatingEndAction();
			}
		}
	}

	template<typename T>
	void ImGuiHandler<T>::Draw() const {
		if (p_Config.GetProcessFunc())
			Internal_SpecificRenderDrawData();
	}

	template<typename T>
	ImGuiHandler<T>::ImGuiHandler(CREF(Window) window)
	: p_Config(window.p_Config->GetImGuiConfig().value())
	, p_LinkedWindow(window){
		Logger::Information("Creating imgui handler...");

		const float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		DEFINE_IMIO_VARIABLE
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		if (p_Config.GetFloatingWindows()) io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		if (p_Config.GetDocking()) io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = nullptr;

		if (p_Config.GetDarkTheme()) ImGui::StyleColorsDark();
		else										     ImGui::StyleColorsLight();

		REF(ImGuiStyle) style = ImGui::GetStyle();
		style.ScaleAllSizes(main_scale);
		style.FontScaleDpi = main_scale;
		SetupImGuiStyle();

		Internal_SpecificInit();

		Logger::Information("Finished creating imgui handler");
	}
	template<typename T>
	ImGuiHandler<T>::~ImGuiHandler() {
		Internal_SpecificShutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}
}