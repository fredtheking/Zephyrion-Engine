#pragma once
#include "cobalt/utils/Macros.hpp"

namespace CE::ST {
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
    Vector2(T xy);

    bool operator==(CREF(Vector2) vector2) const;
    bool operator<(CREF(Vector2) vector2) const;
    bool operator>(CREF(Vector2) vector2) const;
  };
}

template class CE::ST::Vector2<>;
template class CE::ST::Vector2<int>;