#include "Color.hpp"
#define INIT(R, G, B, A) InitRGBA(R, G, B, A); InitElse();
#define INIT_SINGLE(X) INIT(X, X, X, X)


void ZE::ST::Color::InitRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  rgba = {r, g, b, a};
}
void ZE::ST::Color::InitInteger() {
  integer = ToInteger(rgba);
}
void ZE::ST::Color::InitHex() {
  hex = ToHex(rgba);
}
void ZE::ST::Color::InitElse() {
  InitInteger();
  InitHex();
}

void ZE::ST::Color::Update() {
  INIT_SINGLE(0);
}
void ZE::ST::Color::Update(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  INIT(r, g, b, a);
}
void ZE::ST::Color::Update(CREF(RGBA) rgba) {
  INIT(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
void ZE::ST::Color::Update(const Uint32 integer) {
  const auto [red, green, blue, alpha] = ToRGBA(integer);
  INIT(red, green, blue, alpha)
}
void ZE::ST::Color::Update(CREF(std::string) hex) {
  const auto [red, green, blue, alpha] = ToRGBA(hex);
  INIT(red, green, blue, alpha)
}


ZE::ST::RGBA ZE::ST::Color::ToRGBA(const Uint32 integer) {
  return {
    static_cast<unsigned char>(integer>>24  & 0xFF),
    static_cast<unsigned char>(integer>>16  & 0xFF),
    static_cast<unsigned char>(integer>>8  & 0xFF),
    static_cast<unsigned char>(integer  & 0xFF)
  };
}
ZE::ST::RGBA ZE::ST::Color::ToRGBA(CREF(std::string) hex) {
  const uint32_t integer = std::stoul(hex, nullptr, 16);
  return ToRGBA(integer);
}
unsigned int ZE::ST::Color::ToInteger(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  return a << 24 | r << 16 | g << 8 | b;
}
unsigned int ZE::ST::Color::ToInteger(CREF(RGBA) rgba) {
  return ToInteger(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
unsigned int ZE::ST::Color::ToInteger(CREF(std::string) hex) {
  return ToInteger(ToRGBA(hex));
}
std::string ZE::ST::Color::ToHex(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  const uint32_t hex = r << 24 | g << 16 | b << 8 | a;
  std::stringstream ss;
  ss << std::hex << std::setw(8) << std::setfill('0') << hex;
  return ss.str();
}
std::string ZE::ST::Color::ToHex(CREF(RGBA)rgba) {
  return ToHex(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}
std::string ZE::ST::Color::ToHex(const Uint32 integer) {
  return ToHex(ToRGBA(integer));
}


ZE::ST::Color::Color() {
  Update();
}
ZE::ST::Color::Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  Update(r, g, b, a);
}
ZE::ST::Color::Color(const RGBA &rgba) {
  Update(rgba);
}
ZE::ST::Color::Color(const Uint32 integer) {
  Update(integer);
}
ZE::ST::Color::Color(CREF(std::string) hex) {
  Update(hex);
}


bool ZE::ST::Color::operator==(const Color &color) const {
  return rgba == color.rgba &&
         integer == color.integer &&
         hex == color.hex;
}