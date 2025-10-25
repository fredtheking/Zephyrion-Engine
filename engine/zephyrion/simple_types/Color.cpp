#include "Color.hpp"
#define INIT(R, G, B, A) InitRGBA(R, G, B, A); InitElse();
#define INIT_SINGLE(X) INIT(X, X, X, X)


void ZE::ST::Color::InitRGBA(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  rgba = {r, g, b, a};
}
void ZE::ST::Color::InitRGBAfloat() {
  rgba_float = ToRGBAfloat(rgba);
}
void ZE::ST::Color::InitInteger() {
  integer = ToInteger(rgba);
}
void ZE::ST::Color::InitHex() {
  hex = ToHex(rgba);
}
void ZE::ST::Color::InitElse() {
  InitRGBAfloat();
  InitInteger();
  InitHex();
}

void ZE::ST::Color::Update() {
  INIT_SINGLE(0);
}
void ZE::ST::Color::Update(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  INIT(r, g, b, a);
}
void ZE::ST::Color::Update(const float r, const float g, const float b, const float a) {
  const auto [red, green, blue, alpha] = ToRGBA(RGBA{r, g, b, a});
  INIT(red, green, blue, alpha)
}
void ZE::ST::Color::Update(CREF(RGBA<>) rgba) {
  Update(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
void ZE::ST::Color::Update(CREF(RGBA<float>) rgba_float) {
  Update(rgba_float.red, rgba_float.green, rgba_float.blue, rgba_float.alpha);
}
void ZE::ST::Color::Update(const UINT32 integer) {
  const auto [red, green, blue, alpha] = ToRGBA(integer);
  INIT(red, green, blue, alpha)
}
void ZE::ST::Color::Update(CREF(STR) hex) {
  const auto [red, green, blue, alpha] = ToRGBA(hex);
  INIT(red, green, blue, alpha)
}

ZE::ST::RGBA<> ZE::ST::Color::ToRGBA(const float r, const float g, const float b, const float a) {
  return ToRGBA(RGBA{r, g, b, a});
}
ZE::ST::RGBA<> ZE::ST::Color::ToRGBA(const UINT32 integer) {
  return {
    static_cast<UINT8>(integer>>24  & 0xFF),
    static_cast<UINT8>(integer>>16  & 0xFF),
    static_cast<UINT8>(integer>>8  & 0xFF),
    static_cast<UINT8>(integer  & 0xFF)
  };
}
ZE::ST::RGBA<> ZE::ST::Color::ToRGBA(CREF(STR) hex) {
  const UINT32 integer = std::stoul(hex, nullptr, 16);
  return ToRGBA(integer);
}
ZE::ST::RGBA<> ZE::ST::Color::ToRGBA(CREF(RGBA<float>) rgba_float) {
  return {
    static_cast<UINT8>(std::clamp(rgba_float.red * 255.0f, 0.0f, 255.0f)),
    static_cast<UINT8>(std::clamp(rgba_float.green * 255.0f, 0.0f, 255.0f)),
    static_cast<UINT8>(std::clamp(rgba_float.blue * 255.0f, 0.0f, 255.0f)),
    static_cast<UINT8>(std::clamp(rgba_float.alpha * 255.0f, 0.0f, 255.0f))
  };
}

ZE::ST::RGBA<float> ZE::ST::Color::ToRGBAfloat(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  return ToRGBAfloat(RGBA{r, g, b, a});
}
ZE::ST::RGBA<float> ZE::ST::Color::ToRGBAfloat(CREF(RGBA<>) rgba) {
  constexpr float inv = 1.0f / 255.0f;
  return {
    static_cast<float>(rgba.red) * inv,
    static_cast<float>(rgba.green) * inv,
    static_cast<float>(rgba.blue) * inv,
    static_cast<float>(rgba.alpha) * inv
  };
}
ZE::ST::RGBA<float> ZE::ST::Color::ToRGBAfloat(const UINT32 integer) {
  auto [red, green, blue, alpha] = ToRGBA(integer);
  return ToRGBAfloat(red, green, blue, alpha);
}
ZE::ST::RGBA<float> ZE::ST::Color::ToRGBAfloat(CREF(STR) hex) {
  return ToRGBAfloat(ToRGBA(hex));
}

UINT32 ZE::ST::Color::ToInteger(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  return a << 24 | r << 16 | g << 8 | b;
}
UINT32 ZE::ST::Color::ToInteger(const float r, const float g, const float b, const float a) {
  auto [red, green, blue, alpha] = ToRGBA(RGBA{r, g, b, a});
  return ToInteger(red, green, blue, alpha);
}
UINT32 ZE::ST::Color::ToInteger(CREF(RGBA<>) rgba) {
  return ToInteger(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
UINT32 ZE::ST::Color::ToInteger(CREF(RGBA<float>) rgba_float) {
  auto [red, green, blue, alpha] = ToRGBA(rgba_float);
  return ToInteger(red, green, blue, alpha);
}
UINT32 ZE::ST::Color::ToInteger(CREF(STR) hex) {
  return ToInteger(ToRGBA(hex));
}

STR ZE::ST::Color::ToHex(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  const UINT32 hex = r << 24 | g << 16 | b << 8 | a;
  std::stringstream ss;
  ss << std::hex << std::setw(8) << std::setfill('0') << hex;
  return ss.str();
}
STR ZE::ST::Color::ToHex(const float r, const float g, const float b, const float a) {
  return ToHex(RGBA{r, g, b, a});
}
STR ZE::ST::Color::ToHex(CREF(RGBA<>)rgba) {
  return ToHex(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
STR ZE::ST::Color::ToHex(CREF(RGBA<float>) rgba_float) {
  auto [red, green, blue, alpha] = ToRGBA(rgba_float);
  return ToHex(red, green, blue, alpha);
}
STR ZE::ST::Color::ToHex(const UINT32 integer) {
  return ToHex(ToRGBA(integer));
}


ZE::ST::Color::Color() {
  Update();
}
ZE::ST::Color::Color(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a) {
  Update(r, g, b, a);
}
ZE::ST::Color::Color(const float r, const float g, const float b, const float a) {
  Update(r, g, b, a);
}
ZE::ST::Color::Color(CREF(RGBA<>) rgba) {
  Update(rgba);
}
ZE::ST::Color::Color(CREF(RGBA<float>) rgba_float) {
  Update(rgba_float);
}
ZE::ST::Color::Color(const UINT32 integer) {
  Update(integer);
}
ZE::ST::Color::Color(CREF(STR) hex) {
  Update(hex);
}


bool ZE::ST::Color::operator==(CREF(Color) color) const {
  return rgba == color.rgba &&
         integer == color.integer &&
         hex == color.hex;
}

template class ZE::ST::RGBA<>;
template class ZE::ST::RGBA<float>;