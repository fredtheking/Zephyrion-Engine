#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/utils/Enums.hpp"
#include "cobalt/utils/Macros.hpp"

namespace CE {
  class Logger {
  private:
    static void RawPrint(CREF(std::string) prefix, CREF(std::string) msg, EConsoleColor fg_color, EConsoleColor bg_color, bool once = false);
  public:
    static void Separator(CREF(std::string) msg, const char& sign = *"=");
    static void Separator(const EConsoleColor& fg_color = EConsoleColor::Purple, const std::string& msg = "", char sign = *"=");
    static void DebugLog(CREF(std::string) msg, const EConsoleColor& fg_color = EConsoleColor::Skyblue, bool once = false);
    static void Information(CREF(std::string) msg, bool once = false);
    static void Warning(CREF(std::string) msg, bool once = false);
    static void Error(CREF(std::string) msg, bool once = false);
    static void Critical(CREF(std::string) msg, bool once = false);

  private:
    //...
  public:
    //...

  private:
    //...
  public:
    //...
  };
}
