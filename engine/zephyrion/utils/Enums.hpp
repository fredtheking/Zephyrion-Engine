#pragma once
#define ENUM(NAME) enum class NAME
#define BITMASK_ENUMCLASS_OPERATORS(NAME) inline NAME operator|(NAME a, NAME b) {                    \
                                    return static_cast<NAME>(                                    \
                                        static_cast<int>(a) | static_cast<int>(b)                 \
                                    );                                                             \
                                  }                                                                 \
                                  inline NAME operator|=(NAME a, NAME b) {                           \
                                    return a = a | b;                                                 \
                                  }                                                                    \
                                  inline bool operator^(NAME a, NAME b) {                               \
                                    return static_cast<int>(a) & static_cast<int>(b);                    \
                                  }                                                                       \
                                  inline NAME operator&(NAME a, NAME b) {                                  \
                                    return static_cast<NAME>(static_cast<int>(a) & static_cast<int>(b));    \
                                  }                                                                          \
                                  inline NAME operator-(NAME a, NAME b) {                                     \
                                    return static_cast<NAME>(                                                  \
                                      static_cast<int>(a) & ~static_cast<int>(b)                                \
                                    );                                                                           \
                                  }                                                                               \
                                  inline NAME operator-=(NAME a, NAME b) {                                         \
                                    return a = a - b;                                                               \
                                  }

namespace ZE::Enums {
  ENUM(BackendRenderer) {
    OpenGL,
    Vulkan,
    Metal,
  };

  ENUM(WindowPosition) {
    Centered,
    TopLeft,
    Custom,
  };

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

#undef BITMASK_ENUMCLASS_OPERATORS
#undef ENUM