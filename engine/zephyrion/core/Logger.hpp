#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/simple_types/Color.hpp"
#include "zephyrion/utils/Colors.hpp"

namespace ZE {
  class Logger {
  private:
    static int GetConsoleWidth();
    static void PrintTimestamp(CREF(STR) timestamp);
  public:
    static STR GetTimestamp();
    static void RawPrint(CREF(STR) prefix, CREF(STR) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color);
    static void Separator(CREF(STR) msg, char sign = '=');
    static void Separator(CREF(ST::Color) fg_color = Colors::Purple, CREF(STR) msg = "", char sign = '=');
    static void DebugLog(CREF(STR) msg, CREF(ST::Color) fg_color = Colors::SkyBlue);
    static void Information(CREF(STR) msg);
    static void Warning(CREF(STR) msg);
    static void Success(CREF(STR) msg);
    static void Error(CREF(STR) msg);
    static void Critical(CREF(STR) msg);

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

