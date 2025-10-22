#include "Rectangle.hpp"
#define INIT(X, Y, W, H) this->x = X; this->y = Y, this->width = W, this->height = H;
#define INIT_SINGLE(X) INIT(X, X, X, X);


template<typename T>
ZE::ST::Rectangle<T>::Rectangle() {
  INIT_SINGLE(0)
}
template<typename T>
ZE::ST::Rectangle<T>::Rectangle(T x, T y, T width, T height) {
  INIT(x, y, width, height)
}
template<typename T>
ZE::ST::Rectangle<T>::Rectangle(Vector2<T> pos, Vector2<T> size) {
  INIT(pos.x, pos.y, size.x, size.y)
}
template<typename T>
ZE::ST::Rectangle<T>::Rectangle(Vector2<T> pos, T width, T height) {
  INIT(pos.x, pos.y, width, height)
}
template<typename T>
ZE::ST::Rectangle<T>::Rectangle(T x, T y, Vector2<T> size) {
  INIT(x, y, size.x, size.y)
}

template class ZE::ST::Rectangle<>;
template class ZE::ST::Rectangle<int>;