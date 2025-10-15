#pragma once
#include "Vector2.hpp"

namespace CE::ST {
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

template class CE::ST::Rectangle<>;
template class CE::ST::Rectangle<int>;