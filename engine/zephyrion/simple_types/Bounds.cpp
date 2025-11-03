#include "Bounds.hpp"
#define INIT(X, Y, W, H) InitXYWH(X, Y, W, H); InitElse();
#define INIT_SINGLE(X) INIT(X, X, X, X)


namespace ZE::ST {
  template<typename T>
  Bounds<T>::Bounds() {
    Update();
  }
  template<typename T>
  Bounds<T>::Bounds(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, const bool bounds_parameters) {
    Update(x_or_left, y_or_top, width_or_right, height_or_bottom, bounds_parameters);
  }
  template<typename T>
  Bounds<T>::Bounds(CREF(ST_VEC2(T)) pos, CREF(ST_VEC2(T)) size) {
    Update(pos, size);
  }
  template<typename T>
  Bounds<T>::Bounds(CREF(ST_VEC2(T)) pos, CREF(T) width, CREF(T) height) {
    Update(pos, width, height);
  }
  template<typename T>
  Bounds<T>::Bounds(CREF(T) x, CREF(T) y, CREF(ST_VEC2(T)) size) {
    Update(x, y, size);
  }
  template<typename T>
  Bounds<T>::Bounds(CREF(ST_REC(T)) rec) {
    Update(rec);
  }


  template<typename T>
  void Bounds<T>::InitXYWH(CREF(T) x, CREF(T) y, CREF(T) width, CREF(T) height) {
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
  }
  template<typename T>
  void Bounds<T>::InitRectangle() {
    m_Rectangle = {m_X, m_Y, m_Width, m_Height};
  }
  template<typename T>
  void Bounds<T>::InitVectors() {
    m_Position = {m_X, m_Y};
    m_Size = {m_Width, m_Height};
  }
  template<typename T>
  void Bounds<T>::InitBoundsXYWH() {
    m_LeftX = m_X;
    m_RightX = m_X + m_Width;
    m_TopY = m_Y;
    m_BottomY = m_Y + m_Height;
  }
  template<typename T>
  void Bounds<T>::InitBoundsVectors() {
    m_LeftTop = {m_X, m_Y};
    m_RightTop = {m_X + m_Width, m_Y};
    m_LeftBottom = {m_X, m_Y + m_Height};
    m_RightBottom = {m_X + m_Width, m_Y + m_Height};
  }

  template<typename T>
  void Bounds<T>::InitElse() {
    InitRectangle();
    InitVectors();
    InitBoundsXYWH();
    InitBoundsVectors();
  }

  template<typename T>
  void Bounds<T>::Update() {
    INIT_SINGLE(0)
  }
  template<typename T>
  void Bounds<T>::Update(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, const bool bounds_parameters) {
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
  void Bounds<T>::Update(CREF(ST_VEC2(T)) pos, CREF(ST_VEC2(T)) size) {
    INIT(pos.x, pos.y, size.x, size.y)
  }
  template<typename T>
  void Bounds<T>::Update(CREF(ST_VEC2(T)) pos, CREF(T) width, CREF(T) height) {
    INIT(pos.x, pos.y, width, height)
  }
  template<typename T>
  void Bounds<T>::Update(CREF(T) x, CREF(T) y, CREF(ST_VEC2(T)) size) {
    INIT(x, y, size.x, size.y)
  }
  template<typename T>
  void Bounds<T>::Update(CREF(ST_REC(T)) rec) {
    INIT(rec.x, rec.y, rec.width, rec.height)
  }

  template class Bounds<>;
  template class Bounds<int>;
}