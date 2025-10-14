#pragma once
#define ENUM(NAME) enum class NAME

namespace CE::Enums {
  ENUM(WindowPosition) {
    Centered,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
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

  ENUM(BoundsUpdateChanges) {
    XYWH,
    Rectangle,
    Vectors,
    Bounds,
  };
}

#undef MAKE_INTERFACE