#include "Window.hpp"

#include "Input.hpp"
#include "Logger.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/utils/Util.hpp"

void ZE::Window::Internal_UpdateWindowPosition() const {
  ST_VEC2(int) pos;

  switch (p_Config->position_mode_enum) {
    case Enums::ZE_WindowPosition::Centered:
      pos = {SDL_WINDOWPOS_CENTERED};
      break;
    case Enums::ZE_WindowPosition::TopLeft:
      pos = {};
      break;
    case Enums::ZE_WindowPosition::Custom:
      pos = p_Config->position_vec2.value();
      break;
  }

  SDL_SetWindowPosition(p_Window, pos.x, pos.y);
}
void ZE::Window::Internal_UpdateWindowSizeConfigs() const {
  if (p_Config->min_size_vec2 && p_Config->size_vec2 < p_Config->min_size_vec2)
    p_Config->size_vec2 = p_Config->min_size_vec2.value();
  if (p_Config->max_size_vec2 && p_Config->size_vec2 > p_Config->max_size_vec2)
    p_Config->size_vec2 = p_Config->max_size_vec2.value();
}
void ZE::Window::Internal_UpdateWindowSize() const {
  SDL_SetWindowSize(p_Window, p_Config->size_vec2.x, p_Config->size_vec2.y);
}
void ZE::Window::Internal_SetWindowMinimaxSize() const {
  if (p_Config->min_size_vec2)
    SDL_SetWindowMinimumSize(p_Window, p_Config->min_size_vec2->x, p_Config->min_size_vec2->y);
  if (p_Config->max_size_vec2)
    SDL_SetWindowMaximumSize(p_Window, p_Config->max_size_vec2->x, p_Config->max_size_vec2->y);

  Internal_UpdateWindowSize();
}
SDL_WindowFlags ZE::Window::Internal_InitialiseFlags() const {
  SDL_WindowFlags flags = {};

  if (p_Config->opacity_float)
    flags |= SDL_WINDOW_TRANSPARENT;
  if (p_Config->resizable_bool)
    flags |= SDL_WINDOW_RESIZABLE;
  if (p_Config->borderless_bool)
    flags |= SDL_WINDOW_BORDERLESS;
  if (p_Config->fullscreen_bool)
    flags |= SDL_WINDOW_FULLSCREEN;
  if (p_Config->always_on_top_bool)
    flags |= SDL_WINDOW_ALWAYS_ON_TOP;
  if (p_Config->hidden_bool)
    flags |= SDL_WINDOW_HIDDEN;
  if (p_Config->input_blocked_bool)
    flags |= SDL_WINDOW_NOT_FOCUSABLE;
  if (p_Config->external_bool)
    flags |= SDL_WINDOW_EXTERNAL;

  switch (p_Config->renderer_enum) {
    case Enums::ZE_BackendRenderer::OpenGL:
      flags |= SDL_WINDOW_OPENGL; break;
    // bottom ones are for the future. maybe
    case Enums::ZE_BackendRenderer::Vulkan:
      flags |= SDL_WINDOW_VULKAN; break;
    case Enums::ZE_BackendRenderer::Metal:
      flags |= SDL_WINDOW_METAL; break;
  }

  return flags;
}

void ZE::Window::Internal_AfterWindowInit() {
  Internal_SetWindowMinimaxSize();
  Internal_UpdateWindowPosition();

  if (p_Config->modal_parent_pointer) {
    Util::AssertSDL(SDL_SetWindowParent(p_Window, p_Config->modal_parent_pointer), "Failed to make window modal");
  }

  if (!p_Config->icon_filepath_str.empty())
    UpdateIcon(p_Config->icon_filepath_str);
}
void ZE::Window::Internal_HandleResize() {
  for (CREF(SDL_Event) event: Input::GetWindowEvents())
    if (event.type == SDL_EVENT_WINDOW_RESIZED || event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
      glViewport(0, 0, event.window.data1, event.window.data2);
      break;
    }
  //TODO: kinda raw. redo?
  //TODO:2: redid. but still kinda meh?
}

void ZE::Window::Process() {
  if (Input::IsKeyPressed(Enums::ZE_Keys::Backspace))
    SetVsync(!p_Config->vsync_bool);
  if (Input::IsKeyPressed(Enums::ZE_Keys::F11))
    SetFullscreen(!p_Config->fullscreen_bool);
  // TODO: temporary thing. remove later

  Internal_HandleResize();
}
void ZE::Window::Render() {
  if (m_Imgui) DEFINE_IO_VARIABLE

  if (m_Imgui) m_Imgui.value()->Render();
  glClear(GL_COLOR_BUFFER_BIT);
  if (m_Imgui) m_Imgui.value()->Draw();
  SDL_GL_SwapWindow(p_Window);
}

void ZE::Window::UpdateIcon(CREF(std::string) filepath) {
  if (filepath.empty()) {
    if (p_Icon)
      Util::AssertSDL(SDL_SetWindowIcon(p_Window, nullptr), "Failed to clear window icon", "Cleared window icon successfully");
    else
      Logger::Error("Failed to clear window icon: There was never an icon in the first place");
  }
  p_Icon = Util::Loaders::PNGtoSurface(filepath, SDL_PIXELFORMAT_ABGR8888);
  Util::AssertSDL(p_Icon, "Failed to set window icon based on error log above", "Loaded window icon", false, [this]{SDL_SetWindowIcon(p_Window, p_Icon);});
}

void ZE::Window::UpdatePosition(const Enums::ZE_WindowPosition position_mode) const {
  p_Config->position_mode_enum = position_mode;
  p_Config->position_vec2 = NONVALID_ST_VEC2;
  Internal_UpdateWindowPosition();
}
void ZE::Window::UpdatePosition(CREF(ST::Vector2<int>) position) const {
  p_Config->position_mode_enum = Enums::ZE_WindowPosition::Custom;
  p_Config->position_vec2 = position;
  Internal_UpdateWindowPosition();
}
void ZE::Window::UpdatePosition(CREF(ST::Vector2<>) position) const {
  Logger::Warning("Clipping floats to ints. Be careful!");
  UpdatePosition(ST::Vector2{
    static_cast<int>(position.x),
    static_cast<int>(position.y)
  });
}
void ZE::Window::UpdatePosition(const int x, const int y) const {
  UpdatePosition(ST::Vector2{x, y});
}
void ZE::Window::UpdatePosition(const float x, const float y) const {
  UpdatePosition(ST::Vector2{x, y});
}

void ZE::Window::UpdateSize(const ST::Vector2<int> &size) const {
  p_Config->size_vec2 = size;
  Internal_UpdateWindowSizeConfigs();
  Internal_UpdateWindowSize();
}
void ZE::Window::UpdateSize(const ST::Vector2<> &size) const {
  Logger::Warning("Clipping floats to ints. Be careful!");
  UpdateSize(ST::Vector2{
    static_cast<int>(size.x),
    static_cast<int>(size.y)
  });
}
void ZE::Window::UpdateSize(const int width, const int height) const {
  UpdateSize(ST::Vector2{width, height});
}
void ZE::Window::UpdateSize(const float width, const float height) const {
  UpdateSize(ST::Vector2{width, height});
}

void ZE::Window::SetResizable(const bool value) const {
  p_Config->resizable_bool = value;
  SDL_SetWindowResizable(p_Window, p_Config->resizable_bool);
}
void ZE::Window::SetBorderless(const bool value) const {
  p_Config->borderless_bool = value;
  SDL_SetWindowBordered(p_Window, !p_Config->borderless_bool);
}
void ZE::Window::SetFullscreen(const bool value) const {
  p_Config->fullscreen_bool = value;
  SDL_SetWindowFullscreen(p_Window, p_Config->fullscreen_bool);
}
void ZE::Window::SetAlwaysOnTop(const bool value) const {
  p_Config->always_on_top_bool = value;
  SDL_SetWindowAlwaysOnTop(p_Window, p_Config->always_on_top_bool);
}
void ZE::Window::SetHidden(const bool value) const {
  p_Config->hidden_bool = value;
  if (p_Config->hidden_bool)
    SDL_HideWindow(p_Window);
  else
    SDL_ShowWindow(p_Window);
}
void ZE::Window::SetVsync(const bool value) const {
  p_Config->vsync_bool = value;
  SDL_GL_SetSwapInterval(p_Config->vsync_bool);
  //TODO: come up with better implementation for vsync. not cool duplicating "SDL_GL_SetSwapInterval" in both config-init and in set-func
}

ZE::Window::Window(CREF(Configs::WindowConfig) window_config) {
  p_Config = MAKE_SPTR(Configs::WindowConfig)(window_config);
  Logger::Information("Creating window...");

  p_Window = SDL_CreateWindow(
    p_Config->title_str.c_str(),
    p_Config->size_vec2.x,
    p_Config->size_vec2.y,
    Internal_InitialiseFlags()
  );
  Util::AssertSDL(p_Window, "Failed initialising Window", "", true, [this] {Internal_AfterWindowInit();});

  m_GLContext = SDL_GL_CreateContext(p_Window);
  Util::AssertSDL(m_GLContext, "Failed initialising GL context for window", "", true);
  Util::AssertSDL(SDL_GL_MakeCurrent(p_Window, m_GLContext), "Failed initialising GL context for window", "", true);
  Util::AssertSDL(SDL_GL_SetSwapInterval(p_Config->vsync_bool), "Failed setting VSync", "");

  Logger::DebugLog("Current Flags: " + Util::Enums::ToString(SDL_GetWindowFlags(p_Window)));

  if (p_Config->imgui_config)
    m_Imgui = MAKE_UPTR(ImguiHandler)(*this);

  Logger::Information("Finished creating window");
}

ZE::Window::~Window() {
  Logger::Information("Destroying window...");

  Util::AssertSDL(p_Icon, "Failed destroying window icon", "", false, [this]{SDL_DestroySurface(p_Icon);});
  Util::AssertSDL(m_GLContext, "Failed destroying GL context", "Destroyed GL context", false, [this]{SDL_GL_DestroyContext(m_GLContext);});
  Util::AssertSDL(p_Window, "Failed destroying Window", "Destroyed Window", false, [this]{SDL_DestroyWindow(p_Window);});

  Logger::Information("Finished destroying window");
}