#include "Bounds.hpp"
#include "cobalt/utils/Macros.hpp"
#define INIT(X, Y, W, H) InitXYWH(X, Y, W, H); InitElse();
#define INIT_SINGLE(X) INIT(X, X, X, X)


template<typename T>
Cobalt::ST::Bounds<T>::Bounds() {
  Update();
}
template<typename T>
Cobalt::ST::Bounds<T>::Bounds(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, const bool bounds_parameters) {
  Update(x_or_left, y_or_top, width_or_right, height_or_bottom, bounds_parameters);
}
template<typename T>
Cobalt::ST::Bounds<T>::Bounds(CREF(Vector2<T>) pos, CREF(Vector2<T>) size) {
  Update(pos, size);
}
template<typename T>
Cobalt::ST::Bounds<T>::Bounds(CREF(Vector2<T>) pos, CREF(T) width, CREF(T) height) {
  Update(pos, width, height);
}
template<typename T>
Cobalt::ST::Bounds<T>::Bounds(CREF(T) x, CREF(T) y, CREF(Vector2<T>) size) {
  Update(x, y, size);
}
template<typename T>
Cobalt::ST::Bounds<T>::Bounds(CREF(Rectangle<T>) rec) {
  Update(rec);
}


template<typename T>
void Cobalt::ST::Bounds<T>::InitXYWH(CREF(T) x, CREF(T) y, CREF(T) width, CREF(T) height) {
  m_X = x;
  m_Y = y;
  m_Width = width;
  m_Height = height;
}
template<typename T>
void Cobalt::ST::Bounds<T>::InitRectangle() {
  m_Rectangle = {m_X, m_Y, m_Width, m_Height};
}
template<typename T>
void Cobalt::ST::Bounds<T>::InitVectors() {
  m_Position = {m_X, m_Y};
  m_Size = {m_Width, m_Height};
}
template<typename T>
void Cobalt::ST::Bounds<T>::InitBoundsXYWH() {
  m_LeftX = m_X;
  m_RightX = m_X + m_Width;
  m_TopY = m_Y;
  m_BottomY = m_Y + m_Height;
}
template<typename T>
void Cobalt::ST::Bounds<T>::InitBoundsVectors() {
  m_LeftTop = {m_X, m_Y};
  m_RightTop = {m_X + m_Width, m_Y};
  m_LeftBottom = {m_X, m_Y + m_Height};
  m_RightBottom = {m_X + m_Width, m_Y + m_Height};
}

template<typename T>
void Cobalt::ST::Bounds<T>::InitElse() {
  InitRectangle();
  InitVectors();
  InitBoundsXYWH();
  InitBoundsVectors();
}

template<typename T>
void Cobalt::ST::Bounds<T>::Update() {
  INIT_SINGLE(0)
}
template<typename T>
void Cobalt::ST::Bounds<T>::Update(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, const bool bounds_parameters) {
  T width, height;
  const T x = x_or_left;
  const T y = y_or_top;
  if (bounds_parameters) {
    width = width_or_right - x_or_left;
    height = height_or_bottom - y_or_top;
  } else {
    width = width_or_right;
    height = height_or_bottom;
  }
  INIT(x, y, width, height)
}
template<typename T>
void Cobalt::ST::Bounds<T>::Update(CREF(Vector2<T>) pos, CREF(Vector2<T>) size) {
  INIT(pos.x, pos.y, size.x, size.y)
}
template<typename T>
void Cobalt::ST::Bounds<T>::Update(CREF(Vector2<T>) pos, CREF(T) width, CREF(T) height) {
  INIT(pos.x, pos.y, width, height)
}
template<typename T>
void Cobalt::ST::Bounds<T>::Update(CREF(T) x, CREF(T) y, CREF(Vector2<T>) size) {
  INIT(x, y, size.x, size.y)
}
template<typename T>
void Cobalt::ST::Bounds<T>::Update(CREF(Rectangle<T>) rec) {
  INIT(rec.x, rec.y, rec.width, rec.height)
}
