#pragma once
#include "Vector2.hpp"

namespace ZE::ST {
  template <typename T = float>
  class Rectangle {
  private:
    //...
  public:
    //...

  private:
    //...
  public:
    T x, y, width, height;

  private:
    //...
  public:
    Rectangle();
    Rectangle(T x, T y, T width, T height);
    Rectangle(Vector2<T> pos, Vector2<T> size);
    Rectangle(Vector2<T> pos, T width, T height);
    Rectangle(T x, T y, Vector2<T> size);
  };
}

template class ZE::ST::Rectangle<>;
template class ZE::ST::Rectangle<int>;