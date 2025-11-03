#pragma once
#include "Vector2.hpp"
#include "Rectangle.hpp"

namespace ZE::ST {
  template<typename T = float>
  class Bounds {
  private:
    void InitXYWH(CREF(T) x, CREF(T) y, CREF(T) width, CREF(T) height);
    void InitRectangle();
    void InitVectors();
    void InitBoundsXYWH();
    void InitBoundsVectors();

    void InitElse();
  public:
    void Update();
    void Update(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, bool bounds_parameters = false);
    void Update(CREF(ST_VEC2(T)) pos, CREF(ST_VEC2(T)) size);
    void Update(CREF(ST_VEC2(T)) pos, CREF(T) width, CREF(T) height);
    void Update(CREF(T) x, CREF(T) y, CREF(ST_VEC2(T)) size);
    void Update(CREF(ST_REC(T)) rec);

  private:
    //...
  public:
    T m_X, m_Y, m_Width, m_Height;

    ST_REC(T) m_Rectangle;
    ST_VEC2(T) m_Position, m_Size;

    T m_LeftX, m_RightX, m_TopY, m_BottomY;
    ST_VEC2(T) m_LeftTop, m_LeftBottom, m_RightTop, m_RightBottom;

  private:
    //...
  public:
    Bounds();
    Bounds(CREF(T) x_or_left, CREF(T) y_or_top, CREF(T) width_or_right, CREF(T) height_or_bottom, bool bounds_parameters = false);
    Bounds(CREF(ST_VEC2(T)) pos, CREF(ST_VEC2(T)) size);
    Bounds(CREF(ST_VEC2(T)) pos, CREF(T) width, CREF(T) height);
    Bounds(CREF(T) x, CREF(T) y, CREF(ST_VEC2(T)) size);
    explicit Bounds(CREF(ST_REC(T)) rec);
  };
}