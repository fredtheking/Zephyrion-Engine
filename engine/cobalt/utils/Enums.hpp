#pragma once
#define ENUM(NAME) enum class NAME
#define ENUM_FLAG_OPERATORS(NAME) inline NAME operator+(NAME a, NAME b) {                    \
                                    return static_cast<NAME>(                                 \
                                        static_cast<int>(a) | static_cast<int>(b)              \
                                    );                                                          \
                                  }                                                              \
                                  inline NAME operator+=(NAME a, NAME b) {                        \
                                    return a = a + b;                                              \
                                  }                                                                 \
                                  inline bool operator^(NAME a, NAME b) {                            \
                                    return static_cast<int>(a) & static_cast<int>(b);                 \
                                  }                                                                    \
                                  inline NAME operator&(NAME a, NAME b) {                               \
                                    return static_cast<NAME>(static_cast<int>(a) & static_cast<int>(b)); \
                                  }                                                                       \
                                  inline NAME operator-(NAME a, NAME b) {                                  \
                                    return static_cast<NAME>(                                               \
                                      static_cast<int>(a) & ~static_cast<int>(b)                             \
                                    );                                                                        \
                                  }                                                                            \
                                  inline NAME operator-=(NAME a, NAME b) {                                      \
                                    return a = a - b;                                                            \
                                  }

namespace CE::Enums {
  ENUM(WindowPosition) {
    Centered,
    TopLeft,
    Custom,
  };

  ENUM(WindowDynamicFlags) : UINT32 {
    None        = 0,
    Fullscreen  = SDL_WINDOW_FULLSCREEN,
    Hidden      = SDL_WINDOW_HIDDEN,
    Borderless  = SDL_WINDOW_BORDERLESS,
    Resizable   = SDL_WINDOW_RESIZABLE,
    Minimized   = SDL_WINDOW_MINIMIZED,
    Maximized   = SDL_WINDOW_MAXIMIZED,
    AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,
  };
  ENUM_FLAG_OPERATORS(WindowDynamicFlags)

  ENUM(WindowInitFlags) : UINT32 {
    None              = 0,
    OpenGL            = SDL_WINDOW_OPENGL,
    Vulkan            = SDL_WINDOW_VULKAN,
    Metal             = SDL_WINDOW_METAL,
    Transparent       = SDL_WINDOW_TRANSPARENT,
    Occluded          = SDL_WINDOW_OCCLUDED,
    External          = SDL_WINDOW_EXTERNAL,
    Modal             = SDL_WINDOW_MODAL,
    Utility           = SDL_WINDOW_UTILITY,
    Tooltip           = SDL_WINDOW_TOOLTIP,
    PopupMenu         = SDL_WINDOW_POPUP_MENU,
    HighPixelDensity  = SDL_WINDOW_HIGH_PIXEL_DENSITY,
    MouseGrabbed      = SDL_WINDOW_MOUSE_GRABBED,
    MouseCapture      = SDL_WINDOW_MOUSE_CAPTURE,
    MouseRelativeMode = SDL_WINDOW_MOUSE_RELATIVE_MODE,
    MouseFocus        = SDL_WINDOW_MOUSE_FOCUS,
    KeyboardFocused   = SDL_WINDOW_KEYBOARD_GRABBED,
    InputFocus        = SDL_WINDOW_INPUT_FOCUS,
    NotFocusable      = SDL_WINDOW_NOT_FOCUSABLE,
  };
  ENUM_FLAG_OPERATORS(WindowInitFlags)

  ENUM(WindowMode) {
    Windowed,
    Maximized,
    Fullscreen,
    Exclusive,
  };

  ENUM(WindowRenderOption) {
    AspectRatio,
    Stretch,
    TopLeftClip,
    BottomLeftClip,
  };

  ENUM(WindowResolutionOption) {
    WindowSize,
    Custom,
  };
}

#undef ENUM_FLAG_OPERATORS
#undef ENUM