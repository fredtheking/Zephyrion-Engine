#include "Logger.hpp"
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"
#include <fmt/args.h>
#include <fmt/color.h>

#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/window.hpp"

void CE::Logger::RawPrint(CREF(std::string) prefix, CREF(std::string) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color) {
  auto style = fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue));
  if (bg_color != Colors::Blank)
    style |= fmt::bg(fmt::rgb(bg_color.rgba.red, bg_color.rgba.green, bg_color.rgba.blue));

  std::function<void()> format_callback;
  if (!prefix.empty()) {
    std::string good_prefix = Helpers::String::ToUpper(prefix);
    format_callback = [&msg, good_prefix, &style] {
      fmt::print("{}\r", fmt::styled(
        fmt::format("[{}]: {}\n", good_prefix, msg),
        style
      ));
    };
  } else {
    format_callback = [&msg, &style] {
      fmt::print("{}\r", fmt::styled(
        fmt::format("{}\n", msg),
        style
      ));
    };
  }

  format_callback();
  std::cout.flush();
}

void CE::Logger::DebugLog(CREF(std::string) msg, CREF(ST::Color) fg_color) {
  RawPrint("debug", msg, fg_color, Colors::Blank);
}
void CE::Logger::Information(CREF(std::string) msg) {
  RawPrint("info", msg, Colors::White, Colors::Blank);
}
void CE::Logger::Warning(CREF(std::string) msg) {
  RawPrint("warn", msg, Colors::Yellow, Colors::Blank);
}
void CE::Logger::Success(CREF(std::string) msg) {
  RawPrint("success", msg, Colors::Lime, Colors::Blank);
}
void CE::Logger::Error(CREF(std::string) msg) {
  RawPrint("error", msg, Colors::Red, Colors::Blank);
}
// Also crashes the app.
void CE::Logger::Critical(CREF(std::string) msg) {
  RawPrint("crit", msg, Colors::Black, Colors::Red);
  std::exit(-1);
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
      fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue)),
      "{}\n",
      msg
    );
    std::cout.flush();
    return;
  }

  const int filler_len_raw = static_cast<int>(term_width) - static_cast<int>(msg_len) - static_cast<int>(space.length() * 2);
  const size_t filler_len = filler_len_raw > 0 ? filler_len_raw / 2 : 0;
  const std::string filler(filler_len, sign);

  std::string full_line = filler + space + msg + space + filler;
  if (full_line.length() < term_width) {
    full_line += sign;
  }

  fmt::print(
      fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue)),
      "{}\n\r",
      full_line
    );
  std::cout.flush();
  #if !defined(_WIN32) && !defined(_WIN64)
  std::cout << "\n";
  #endif
}
