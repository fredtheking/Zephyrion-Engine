#pragma once
#include "zephyrion/pch.hpp"

namespace ZE::ST {
  template <typename T = float>
  class Vector2 {
  private:
    //...
  public:
    //...

  private:
    //...
  public:
    T x, y;

  private:
    //...
  public:
    Vector2();
    Vector2(CREF(Vector2) vector2);
    Vector2(T x, T y);
    explicit Vector2(T xy);

    bool operator==(CREF(Vector2) vector2) const;
    bool operator<(CREF(Vector2) vector2) const;
    bool operator>(CREF(Vector2) vector2) const;
  };
}