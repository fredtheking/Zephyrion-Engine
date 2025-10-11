#pragma once

namespace Cobalt::ST {
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
    Vector2(T x, T y);
    explicit Vector2(T xy);
  };
}