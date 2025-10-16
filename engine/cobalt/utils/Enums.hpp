#pragma once
#define ENUM(NAME) enum class NAME
#define ENUM_FLAG_OPERATORS(NAME) inline NAME operator+(NAME a, NAME b) {       \
                                    return static_cast<NAME>(                    \
                                        static_cast<int>(a) | static_cast<int>(b) \
                                    );                                             \
                                  }                                                 \
                                  inline NAME operator+=(NAME a, NAME b) {           \
                                    return a = a + b;                                 \
                                  }                                                    \
                                  inline bool operator==(NAME a, NAME b) {              \
                                    return static_cast<int>(a) & static_cast<int>(b);    \
                                  }                                                       \
                                  inline NAME operator-(NAME a, NAME b) {                  \
                                    return static_cast<NAME>(                               \
                                      static_cast<int>(a) & ~static_cast<int>(b)             \
                                    );                                                        \
                                  }                                                            \
                                  inline NAME operator-=(NAME a, NAME b) {                      \
                                    return a = a - b;                                             \
                                  }

namespace CE::Enums {
  ENUM(WindowPosition) {
    Centered,
    TopLeft,
    Custom,
  };

  ENUM(WindowFlags) {
    Fullscreen = 1 << 0,
    Occluded = 1 << 1,
    Hidded = 1 << 2,
    Borderless = 1 << 3,
    Resizable = 1 << 4,
    Minimized = 1 << 5,
    Maximized = 1 << 6,
    AlwaysOnTop = 1 << 7,
  };
  ENUM_FLAG_OPERATORS(WindowFlags)

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