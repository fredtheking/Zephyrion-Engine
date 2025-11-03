#include "Color.hpp"
#define INIT(R, G, B, A) InitRGBA(R, G, B, A); InitElse();
#define INIT_SINGLE(X) INIT(X, X, X, X)


namespace ZE::ST {
  void Color::InitRGBA(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    rgba = {r, g, b, a};
  }
  void Color::InitRGBAfloat() {
    rgba_float = ToRGBAfloat(rgba);
  }
  void Color::InitInteger() {
    integer = ToInteger(rgba);
  }
  void Color::InitHex() {
    hex = ToHex(rgba);
  }
  void Color::InitElse() {
    InitRGBAfloat();
    InitInteger();
    InitHex();
  }

  void Color::Update() {
    INIT_SINGLE(0);
  }
  void Color::Update(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    INIT(r, g, b, a);
  }
  void Color::Update(const float r, const float g, const float b, const float a) {
    const auto [red, green, blue, alpha] = ToRGBA(RGBA{r, g, b, a});
    INIT(red, green, blue, alpha)
  }
  void Color::Update(CREF(RGBA<>) rgba) {
    Update(rgba.red, rgba.green, rgba.blue, rgba.alpha);
  }
  void Color::Update(CREF(RGBA<float>) rgba_float) {
    Update(rgba_float.red, rgba_float.green, rgba_float.blue, rgba_float.alpha);
  }
  void Color::Update(const Z_UINT32 integer) {
    const auto [red, green, blue, alpha] = ToRGBA(integer);
    INIT(red, green, blue, alpha)
  }
  void Color::Update(CREF(STR) hex) {
    const auto [red, green, blue, alpha] = ToRGBA(hex);
    INIT(red, green, blue, alpha)
  }

  RGBA<> Color::ToRGBA(const float r, const float g, const float b, const float a) {
    return ToRGBA(RGBA{r, g, b, a});
  }
  RGBA<> Color::ToRGBA(const Z_UINT32 integer) {
    return {
      static_cast<Z_UINT8>(integer>>24  & 0xFF),
      static_cast<Z_UINT8>(integer>>16  & 0xFF),
      static_cast<Z_UINT8>(integer>>8  & 0xFF),
      static_cast<Z_UINT8>(integer  & 0xFF)
    };
  }
  RGBA<> Color::ToRGBA(CREF(STR) hex) {
    const Z_UINT32 integer = std::stoul(hex, nullptr, 16);
    return ToRGBA(integer);
  }
  RGBA<> Color::ToRGBA(CREF(RGBA<float>) rgba_float) {
    return {
      static_cast<Z_UINT8>(std::clamp(rgba_float.red * 255.0f, 0.0f, 255.0f)),
      static_cast<Z_UINT8>(std::clamp(rgba_float.green * 255.0f, 0.0f, 255.0f)),
      static_cast<Z_UINT8>(std::clamp(rgba_float.blue * 255.0f, 0.0f, 255.0f)),
      static_cast<Z_UINT8>(std::clamp(rgba_float.alpha * 255.0f, 0.0f, 255.0f))
    };
  }

  RGBA<float> Color::ToRGBAfloat(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    return ToRGBAfloat(RGBA{r, g, b, a});
  }
  RGBA<float> Color::ToRGBAfloat(CREF(RGBA<>) rgba) {
    constexpr float inv = 1.0f / 255.0f;
    return {
      static_cast<float>(rgba.red) * inv,
      static_cast<float>(rgba.green) * inv,
      static_cast<float>(rgba.blue) * inv,
      static_cast<float>(rgba.alpha) * inv
    };
  }
  RGBA<float> Color::ToRGBAfloat(const Z_UINT32 integer) {
    auto [red, green, blue, alpha] = ToRGBA(integer);
    return ToRGBAfloat(red, green, blue, alpha);
  }
  RGBA<float> Color::ToRGBAfloat(CREF(STR) hex) {
    return ToRGBAfloat(ToRGBA(hex));
  }

  Z_UINT32 Color::ToInteger(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    return a << 24 | r << 16 | g << 8 | b;
  }
  Z_UINT32 Color::ToInteger(const float r, const float g, const float b, const float a) {
    auto [red, green, blue, alpha] = ToRGBA(RGBA{r, g, b, a});
    return ToInteger(red, green, blue, alpha);
  }
  Z_UINT32 Color::ToInteger(CREF(RGBA<>) rgba) {
    return ToInteger(rgba.red, rgba.green, rgba.blue, rgba.alpha);
  }
  Z_UINT32 Color::ToInteger(CREF(RGBA<float>) rgba_float) {
    auto [red, green, blue, alpha] = ToRGBA(rgba_float);
    return ToInteger(red, green, blue, alpha);
  }
  Z_UINT32 Color::ToInteger(CREF(STR) hex) {
    return ToInteger(ToRGBA(hex));
  }

  STR Color::ToHex(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    const Z_UINT32 hex = r << 24 | g << 16 | b << 8 | a;
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << hex;
    return ss.str();
  }
  STR Color::ToHex(const float r, const float g, const float b, const float a) {
    return ToHex(RGBA{r, g, b, a});
  }
  STR Color::ToHex(CREF(RGBA<>)rgba) {
    return ToHex(rgba.red, rgba.green, rgba.blue, rgba.alpha);
  }
  STR Color::ToHex(CREF(RGBA<float>) rgba_float) {
    auto [red, green, blue, alpha] = ToRGBA(rgba_float);
    return ToHex(red, green, blue, alpha);
  }
  STR Color::ToHex(const Z_UINT32 integer) {
    return ToHex(ToRGBA(integer));
  }


  Color::Color() {
    Update();
  }
  Color::Color(const Z_UINT8 r, const Z_UINT8 g, const Z_UINT8 b, const Z_UINT8 a) {
    Update(r, g, b, a);
  }
  Color::Color(const float r, const float g, const float b, const float a) {
    Update(r, g, b, a);
  }
  Color::Color(CREF(RGBA<>) rgba) {
    Update(rgba);
  }
  Color::Color(CREF(RGBA<float>) rgba_float) {
    Update(rgba_float);
  }
  Color::Color(const Z_UINT32 integer) {
    Update(integer);
  }
  Color::Color(CREF(STR) hex) {
    Update(hex);
  }


  bool Color::operator==(CREF(Color) color) const {
    return rgba == color.rgba &&
           integer == color.integer &&
           hex == color.hex;
  }

  template class RGBA<>;
  template class RGBA<float>;
}