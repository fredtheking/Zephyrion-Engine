#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/simple_types/Color.hpp"
#include "zephyrion/utils/Colors.hpp"
#define Z_FMT_FORMAT fmt::format(fmt, std::forward<Args>(args)...)

namespace ZE {
  class Logger {
  INTERNAL_GUARD_BEGIN
    template<typename... Args>
    static void DebugLog(fmt::format_string<Args...> fmt, Args&&... args){ DebugLog(Z_FMT_FORMAT); }
    static void DebugLog(CREF(STR) msg);

    static int Internal_GetConsoleWidth();
    static void Internal_RawPrint(CREF(STR) prefix, CREF(STR) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color);
    static STR Internal_GetTimestamp();
    static void Internal_PrintTimestamp(CREF(STR) timestamp);
  INTERNAL_GUARD_END
  public:
    static void Separator(CREF(STR) msg, char sign = '=');
    static void Separator(CREF(ST::Color) fg_color = Colors::Purple, CREF(STR) msg = "", char sign = '=');
    template<typename... Args>
    static void Information(fmt::format_string<Args...> fmt, Args&&... args){ Information(Z_FMT_FORMAT); }
    static void Information(CREF(STR) msg);
    template<typename... Args>
    static void Warning(fmt::format_string<Args...> fmt, Args&&... args){ Warning(Z_FMT_FORMAT); }
    static void Warning(CREF(STR) msg);
    template<typename... Args>
    static void Success(fmt::format_string<Args...> fmt, Args&&... args){ Success(Z_FMT_FORMAT); }
    static void Success(CREF(STR) msg);
    template<typename... Args>
    static void Error(fmt::format_string<Args...> fmt, Args&&... args){ Error(Z_FMT_FORMAT); }
    static void Error(CREF(STR) msg);
    // Also crashes the app.
    template<typename... Args>
    static void Critical(fmt::format_string<Args...> fmt, Args&&... args){ Critical(Z_FMT_FORMAT); std::exit(-1); }
    static void Critical(CREF(STR) msg);

  private:
    //...
  public:
    //...

  private:
    friend class Window;
  public:
    STATIC_ONLY_CONSTRUCTOR(Logger)
  };
}

#undef Z_FMT_FORMAT
