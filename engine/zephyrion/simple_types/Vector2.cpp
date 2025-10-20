#include "Vector2.hpp"

#include "zephyrion/utils/Macros.hpp"
#define INIT(X, Y) this->x = X; this->y = Y;
#define INIT_SINGLE(X) INIT(X, X);


template<typename T>
ZE::ST::Vector2<T>::Vector2() {
  INIT_SINGLE(0)
}
template<typename T>
ZE::ST::Vector2<T>::Vector2(T x, T y) {
  INIT(x, y)
}
template<typename T>
ZE::ST::Vector2<T>::Vector2(T xy) {
  INIT_SINGLE(xy)
}

template<typename T>
bool ZE::ST::Vector2<T>::operator==(CREF(Vector2) vector2) const {
  return x == vector2.x &&
         y == vector2.y;
}
template<typename T>
bool ZE::ST::Vector2<T>::operator<(CREF(Vector2) vector2) const {
  return x < vector2.x ||
         y < vector2.y;
}
template<typename T>
bool ZE::ST::Vector2<T>::operator>(CREF(Vector2) vector2) const {
  return x > vector2.x ||
         y > vector2.y;
}
