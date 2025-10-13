#pragma once
#include "cobalt/pch.hpp"

namespace Cobalt::ST {
  class Color {
  private:
    //...
  public:
    //...

  private:
    //...
  public:
    const unsigned char red;
    const unsigned char green;
    const unsigned char blue;
    const unsigned char alpha;

    const std::string hex;
    const unsigned int integer;

  private:
    //...
  public:
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    Color(unsigned int integer);
    Color(std::string hex);
    ~Color();
  };

  #define DEFINE_COLOR(NAME, R, G, B) static inline Color NAME {R, G, B, 255};
  #define DEFINE_COLOR_SINGLE(NAME, X) DEFINE_COLOR(NAME, X, X, X)

  DEFINE_COLOR_SINGLE(White, 255)
  DEFINE_COLOR_SINGLE(DimWhite, 230)

  DEFINE_COLOR_SINGLE(BrightLightGray, 217)
  DEFINE_COLOR_SINGLE(LightGray, 192)
  DEFINE_COLOR_SINGLE(DimLightGray, 167)

  DEFINE_COLOR_SINGLE(BrightGray, 153)
  DEFINE_COLOR_SINGLE(Gray, 128)
  DEFINE_COLOR_SINGLE(DimGray, 103)

  DEFINE_COLOR_SINGLE(BrightDarkGray, 89)
  DEFINE_COLOR_SINGLE(DarkGray, 64)
  DEFINE_COLOR_SINGLE(DimDarkGray, 39)

  DEFINE_COLOR_SINGLE(BrightBlack, 25)
  DEFINE_COLOR_SINGLE(Black, 0)

  DEFINE_COLOR(Red, 255, 0, 0)
  DEFINE_COLOR(Lime, 0, 255, 0)
  DEFINE_COLOR(Blue, 0, 0, 255)
  DEFINE_COLOR(Green, 0, 128, 0)
  DEFINE_COLOR(Yellow, 255, 255, 0)
  DEFINE_COLOR(Cyan, 0, 255, 255)
  DEFINE_COLOR(Magenta, 255, 0, 255)
  DEFINE_COLOR(Purple, 128, 0, 128)

  #undef DEFINE_COLOR_SINGLE
  #undef DEFINE_COLOR
}

namespace std {
  std::string std::to_string(Color color) {
    std::stringstream ss;
    ss << "Color(" << color.ToInt() << ")";
  }
}