#include "Vector2.hpp"
#define INIT(X, Y) this->x = X; this->y = Y;
#define INIT_SINGLE(X) INIT(X, X);


template<typename T>
Cobalt::ST::Vector2<T>::Vector2() {
  INIT_SINGLE(0)
}
template<typename T>
Cobalt::ST::Vector2<T>::Vector2(T x, T y) {
  INIT(x, y)
}
template<typename T>
Cobalt::ST::Vector2<T>::Vector2(T xy) {
  INIT_SINGLE(xy)
}