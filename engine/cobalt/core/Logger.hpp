#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/simple_types/Color.hpp"
#include "cobalt/utils/Colors.hpp"

namespace CE {
  class Logger {
  private:
    //...
  public:
    static std::string GetTimestamp();
    static void RawPrint(CREF(std::string) prefix, CREF(std::string) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color);
    static void Separator(CREF(std::string) msg, char sign = '=');
    static void Separator(CREF(ST::Color) fg_color = Colors::Purple, const std::string& msg = "", char sign = '=');
    static void DebugLog(CREF(std::string) msg, CREF(ST::Color) fg_color = Colors::SkyBlue);
    static void Information(CREF(std::string) msg);
    static void Warning(CREF(std::string) msg);
    static void Success(CREF(std::string) msg);
    static void Error(CREF(std::string) msg);
    static void Critical(CREF(std::string) msg);

  private:
    //...
  public:
    //...

  private:
    //...
  public:
    STATIC_ONLY_CONSTRUCTOR(Logger)
  };
}

