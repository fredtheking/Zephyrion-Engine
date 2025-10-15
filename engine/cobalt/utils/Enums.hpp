#pragma once
#define ENUM(NAME) enum class NAME

namespace CE::Enums {
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

#undef ENUM