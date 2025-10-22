#pragma once
#include "zephyrion/pch.hpp"

namespace ZE::ST {
  /**
   * Struct that holds R, G, B and A values. Each is Uint8 (unsigned int).
   */
  struct RGBA {
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;

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
    void InitRGBA(UINT8 r, Uint8 g, Uint8 b, Uint8 a);
    void InitInteger();
    void InitHex();

    void InitElse();
  public:
    void Update();
    void Update(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void Update(CREF(RGBA) rgba);
    void Update(Uint32 integer);
    void Update(CREF(std::string) hex);

    static RGBA ToRGBA(Uint32 integer);
    static RGBA ToRGBA(CREF(std::string) hex);
    static Uint32 ToInteger(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    static Uint32 ToInteger(CREF(RGBA) rgba);
    static Uint32 ToInteger(CREF(std::string) hex);
    static std::string ToHex(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    static std::string ToHex(CREF(RGBA) rgba);
    static std::string ToHex(Uint32 integer);

  private:
    //...
  public:
    RGBA rgba;
    Uint32 integer;
    std::string hex;

  private:
    //...
  public:
    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color(CREF(RGBA) rgba);
    Color(Uint32 integer);
    Color(CREF(std::string) hex);

    bool operator==(const Color & color) const;
  };
}