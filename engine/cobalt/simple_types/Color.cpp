#include "Color.hpp"

Cobalt::ST::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
: red(r)
, green(g)
, blue(b)
, alpha(a) {}
Cobalt::ST::Color::Color(unsigned int integer) {

}
Cobalt::ST::Color::Color(std::string hex) {

}

Cobalt::ST::Color::~Color() {

}

