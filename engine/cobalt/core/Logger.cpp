#include "Logger.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"
#include <fmt/args.h>
#include <fmt/color.h>

#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/window.hpp"

std::vector<std::string> oncers = {};

void CE::Logger::RawPrint(const std::string &prefix, CREF(std::string) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color) {
  fmt::print(
    fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue)) |
    fmt::bg(fmt::rgb(0, 0, 0)),
    "[{}]: {}\n",
    Low::Helpers::String::ToUpper(prefix), msg
  );
}

void CE::Logger::DebugLog(CREF(std::string) msg, CREF(ST::Color) fg_color) {
  RawPrint("debug", msg, fg_color, Colors::Black);
}
void CE::Logger::Information(CREF(std::string) msg) {
  RawPrint("info", msg, Colors::White, Colors::Blank);
}
void CE::Logger::Warning(CREF(std::string) msg) {
  RawPrint("warn", msg, Colors::Yellow, Colors::Blank);
}
void CE::Logger::Error(CREF(std::string) msg) {
  RawPrint("error", msg, Colors::Red, Colors::Blank);
}
// Also crashes the game.
void CE::Logger::Critical(CREF(std::string) msg) {
  RawPrint("crit", msg, Colors::Black, Colors::Red);
  std::abort();
}


void CE::Logger::Separator(CREF(std::string) msg, const char sign) {
  Separator(Colors::Purple, msg, sign);
}
void CE::Logger::Separator(CREF(ST::Color) fg_color, CREF(std::string) msg, const char sign) {
  const size_t term_width = Term::screen_size().columns();
  const std::string space = msg.empty() ? "" : "  ";
  const size_t msg_len = msg.length();

  if (msg_len + space.length() * 2 >= term_width) {
    fmt::print(
      fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue)) |
      fmt::bg(fmt::rgb(0, 0, 0)),
      "{}\n",
      msg
    );
    return;
  }

  const int filler_len_raw = static_cast<int>(term_width) - static_cast<int>(msg_len) - static_cast<int>(space.length() * 2);
  const size_t filler_len = filler_len_raw > 0 ? filler_len_raw / 2 : 0;
  const std::string filler(filler_len, sign);

  std::string full_line = filler + space + msg + space + filler;
  if (full_line.length() < term_width) {
    full_line += sign;
  }

  std::cout << TerminalManager::ToFgColor(fg_color, full_line);
  #if !defined(_WIN32) && !defined(_WIN64)
  std::cout << "\n";
  #endif
}
