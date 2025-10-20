#include "Window.hpp"
#include "Logger.hpp"
#include "cobalt/utils/Macros.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Util.hpp"

void CE::Window::Internal_UpdateWindowPosition() const {
  ST::Vector2<int> pos;

  switch (p_Config.position_mode_enum) {
    case Enums::WindowPosition::Centered:
      pos = {SDL_WINDOWPOS_CENTERED};
      break;
    case Enums::WindowPosition::TopLeft:
      pos = {};
      break;
    case Enums::WindowPosition::Custom:
      pos = p_Config.position_vec2;
      break;
  }

  SDL_SetWindowPosition(p_Window, pos.x, pos.y);
}
void CE::Window::Internal_UpdateWindowSize() const {
  SDL_SetWindowSize(p_Window, p_Config.size_vec2.x, p_Config.size_vec2.y);
}
void CE::Window::Internal_SetWindowMinimaxSize() const {
  if (p_Config.min_size_vec2 != NONVALID_VEC2)
    SDL_SetWindowMinimumSize(p_Window, p_Config.min_size_vec2.x, p_Config.min_size_vec2.y);
  if (p_Config.max_size_vec2 != NONVALID_VEC2)
    SDL_SetWindowMaximumSize(p_Window, p_Config.max_size_vec2.x, p_Config.max_size_vec2.y);

  Internal_UpdateWindowSize();
}
SDL_WindowFlags CE::Window::Internal_InitialiseFlags() const {
  SDL_WindowFlags flags = SDL_WINDOW_OPENGL;

  if (p_Config.opacity_float < 1.0f)
    flags |= SDL_WINDOW_TRANSPARENT;
  if (p_Config.resizable_bool)
    flags |= SDL_WINDOW_RESIZABLE;
  if (p_Config.borderless_bool)
    flags |= SDL_WINDOW_BORDERLESS;
  if (p_Config.fullscreen_bool)
    flags |= SDL_WINDOW_FULLSCREEN;
  if (p_Config.always_on_top_bool)
    flags |= SDL_WINDOW_ALWAYS_ON_TOP;
  if (p_Config.input_blocked_bool)
    flags |= SDL_WINDOW_NOT_FOCUSABLE;
  if (p_Config.external_bool)
    flags |= SDL_WINDOW_EXTERNAL;


  switch (p_Config.renderer_enum) {
    case Enums::BackendRenderer::OpenGL:
      flags |= SDL_WINDOW_OPENGL; break;
    case Enums::BackendRenderer::Vulkan:
      flags |= SDL_WINDOW_VULKAN; break;
    case Enums::BackendRenderer::Metal:
      flags |= SDL_WINDOW_METAL; break;
  }

  return flags;
}

void CE::Window::Internal_AfterWindowInit() {
  Internal_SetWindowMinimaxSize();
  Internal_UpdateWindowPosition();

  if (p_Config.modal_parent_pointer) {
    Util::AssertSDL(SDL_SetWindowParent(p_Window, p_Config.modal_parent_pointer), "Failed to make window modal");
  }

  if (!p_Config.icon_filepath_str.empty())
    UpdateIcon(p_Config.icon_filepath_str);
}

void CE::Window::UpdateIcon(CREF(std::string) filepath) {
  if (filepath.empty()) {
    if (p_Icon)
      Util::AssertSDL(SDL_SetWindowIcon(p_Window, nullptr), "Failed to clear window icon", "Cleared window icon successfully");
    else
      Logger::Error("Failed to clear window icon: There was never an icon in the first place");
  }
  p_Icon = Util::Loaders::PNGtoSurface(filepath, SDL_PIXELFORMAT_ABGR8888);
  Util::AssertSDL(p_Icon, "Failed to set window icon based on error log above", "Loaded window icon", false, [this]{SDL_SetWindowIcon(p_Window, p_Icon);});
}

void CE::Window::UpdatePosition(const Enums::WindowPosition position_mode) const {
  p_Config.position_mode_enum = position_mode;
  p_Config.position_vec2 = NONVALID_VEC2;
  Internal_UpdateWindowPosition();
}
void CE::Window::UpdatePosition(CREF(ST::Vector2<int>) position) const {
  p_Config.position_mode_enum = Enums::WindowPosition::Custom;
  p_Config.position_vec2 = position;
  Internal_UpdateWindowPosition();
}
void CE::Window::UpdatePosition(CREF(ST::Vector2<>) position) const {
  Logger::Warning("Clipping floats to ints. Be careful!");
  UpdatePosition(ST::Vector2{
    static_cast<int>(position.x),
    static_cast<int>(position.y)
  });
}
void CE::Window::UpdatePosition(const int x, const int y) const {
  UpdatePosition(ST::Vector2{x, y});
}
void CE::Window::UpdatePosition(const float x, const float y) const {
  UpdatePosition(ST::Vector2{x, y});
}

void CE::Window::UpdateSize(const ST::Vector2<int> &size) const {
  p_Config.size_vec2 = size;
  Internal_UpdateWindowSize();
}
void CE::Window::UpdateSize(const ST::Vector2<> &size) const {
  Logger::Warning("Clipping floats to ints. Be careful!");
  UpdateSize(ST::Vector2{
    static_cast<int>(size.x),
    static_cast<int>(size.y)
  });
}
void CE::Window::UpdateSize(const int width, const int height) const {
  UpdateSize(ST::Vector2{width, height});
}
void CE::Window::UpdateSize(const float width, const float height) const {
  UpdateSize(ST::Vector2{width, height});
}

void CE::Window::SetResizable(const bool value) const {
  p_Config.resizable_bool = value;
  SDL_SetWindowResizable(p_Window, p_Config.resizable_bool);
}
void CE::Window::SetBorderless(const bool value) const {
  p_Config.borderless_bool = value;
  SDL_SetWindowBordered(p_Window, !p_Config.borderless_bool);
}
void CE::Window::SetFullscreen(const bool value) const {
  p_Config.fullscreen_bool = value;
  SDL_SetWindowFullscreen(p_Window, p_Config.fullscreen_bool);
}
void CE::Window::SetAlwaysOnTop(const bool value) const {
  p_Config.always_on_top_bool = value;
  SDL_SetWindowAlwaysOnTop(p_Window, p_Config.always_on_top_bool);
}

CE::Window::Window(REF(Configs::WindowConfig) window_config)
: p_Config(window_config){
  Logger::Information("Creating window...");

  p_Window = SDL_CreateWindow(
    p_Config.title_str.c_str(),
    p_Config.size_vec2.x,
    p_Config.size_vec2.y,
    Internal_InitialiseFlags()
  );
  Util::AssertSDL(p_Window, "Failed initialising Window", "", true, [this] {Internal_AfterWindowInit();});

  p_Renderer = SDL_CreateRenderer(p_Window, nullptr);
  Util::AssertSDL(p_Renderer, "Failed initialising Renderer for window", "", true);

  Logger::DebugLog("Current Flags: " + Util::Enums::ToString(SDL_GetWindowFlags(p_Window)));

  Logger::Information("Finished creating window");
}

CE::Window::~Window() {
  Logger::Information("Destroying window...");

  Util::AssertSDL(p_Renderer, "Failed destroying Renderer", "Destroyed Renderer", false, [this]{SDL_DestroyRenderer(p_Renderer);});
  Util::AssertSDL(p_Window, "Failed destroying Window", "Destroyed Window", false, [this]{SDL_DestroyWindow(p_Window);});

  Logger::Information("Finished destroying window");
}

