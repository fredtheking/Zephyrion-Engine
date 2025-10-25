#pragma once
#include "zephyrion/pch.hpp"

namespace ZE::ST {
  /**
   * Struct that holds R, G, B and A values. Each is UINT8 (unsigned char).
   */
  template<typename COLOR_TYPE = UINT8>
  struct RGBA {
    COLOR_TYPE red;
    COLOR_TYPE green;
    COLOR_TYPE blue;
    COLOR_TYPE alpha;

    bool operator==(CREF(RGBA) rgba) const {
      return red == rgba.red &&
             green == rgba.green &&
             blue == rgba.blue &&
             alpha == rgba.alpha;
    }
  };

  /**
   * Smart color class. Contains RGBA struct, Uint32 (unsigned int) rgba form and hex string.
   */
  class Color {
  private:
    void InitRGBA(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    void InitRGBAfloat();
    void InitInteger();
    void InitHex();

    void InitElse();
  public:
    void Update();
    void Update(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    void Update(float r, float g, float b, float a);
    void Update(CREF(RGBA<>) rgba);
    void Update(CREF(RGBA<float>) rgba_float);
    void Update(UINT32 integer);
    void Update(CREF(STR) hex);

    static RGBA<> ToRGBA(float r, float g, float b, float a);
    static RGBA<> ToRGBA(UINT32 integer);
    static RGBA<> ToRGBA(CREF(STR) hex);
    static RGBA<> ToRGBA(CREF(RGBA<float>) rgba_float);
    static RGBA<float> ToRGBAfloat(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    static RGBA<float> ToRGBAfloat(CREF(RGBA<>) rgba);
    static RGBA<float> ToRGBAfloat(UINT32 integer);
    static RGBA<float> ToRGBAfloat(CREF(STR) hex);
    static UINT32 ToInteger(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    static UINT32 ToInteger(float r, float g, float b, float a);
    static UINT32 ToInteger(CREF(RGBA<>) rgba);
    static UINT32 ToInteger(CREF(RGBA<float>) rgba_float);
    static UINT32 ToInteger(CREF(STR) hex);
    static STR ToHex(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    static STR ToHex(float r, float g, float b, float a);
    static STR ToHex(CREF(RGBA<>) rgba);
    static STR ToHex(CREF(RGBA<float>) rgba_float);
    static STR ToHex(UINT32 integer);

  private:
    //...
  public:
    RGBA<> rgba = {};
    RGBA<float> rgba_float = {};
    UINT32 integer = 0;
    STR hex = "000000";

  private:
    //...
  public:
    Color();
    Color(UINT8 r, UINT8 g, UINT8 b, UINT8 a);
    Color(float r, float g, float b, float a);
    explicit Color(CREF(RGBA<>) rgba);
    explicit Color(CREF(RGBA<float>) rgba_float);
    explicit Color(UINT32 integer);
    explicit Color(CREF(STR) hex);

    bool operator==(CREF(Color) color) const;
  };
}