#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/utils/Macros.hpp"

namespace CE::ST {
  /**
   * Struct that holds R, G, B and A values. Each is Uint8 (unsigned int).
   */
  struct RGBA {
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
  };

  /**
   * Smart color class. Contains RGBA struct, Uint32 (unsigned int) rgba form and hex string.
   */
  class Color {
  private:
    void InitRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
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
    std::string hex;
    Uint32 integer;

  private:
    //...
  public:
    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    explicit Color(CREF(RGBA) rgba);
    explicit Color(Uint32 integer);
    explicit Color(CREF(std::string) hex);
  };
}