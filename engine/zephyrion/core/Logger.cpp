#include "Logger.hpp"
#include "zephyrion/pch.hpp"
#include "zephyrion/utils/Util.hpp"

constexpr int MSG_START_POINT = 12;

#ifdef _WIN32
#undef UINT8
#undef UINT16
#undef UINT32
#undef UINT64
#include <Windows.h>
int ZE::Logger::GetConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
#else
#include <sys/ioctl.h>
#include <unistd.h>
int ZE::Logger::GetConsoleWidth() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}
#endif


void ZE::Logger::PrintTimestamp(CREF(STR) timestamp) {
  const ST::RGBA rgba = Colors::Silver.rgba;
  fmt::print(
    fmt::fg(fmt::rgb(rgba.red, rgba.green, rgba.blue)),
    "{}",
    '[' + timestamp + "] "
  );
}
STR ZE::Logger::GetTimestamp() {
  const auto now = std::chrono::system_clock::now();

  std::time_t t = std::chrono::system_clock::to_time_t(now);
  std::tm local{};

#ifdef _WIN32
  localtime_s(&local, &t);
#else
  localtime_r(&t, &local);
#endif

  const auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
  std::ostringstream oss;

  oss << std::put_time(&local, "%d-%m-%y %H:%M:%S.")
      << std::setw(3) << std::setfill('0') << ms.count();

  return oss.str();
}

void ZE::Logger::RawPrint(CREF(STR) prefix, CREF(STR) msg, CREF(ST::Color) fg_color, CREF(ST::Color) bg_color) {
  auto style = fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue));
  if (bg_color != Colors::Blank)
    style |= fmt::bg(fmt::rgb(bg_color.rgba.red, bg_color.rgba.green, bg_color.rgba.blue));

  std::function<void()> format_callback;
  if (!prefix.empty()) {
    STR good_prefix = Util::String::ToUpper(prefix);
    const int msg_startspace_len = MSG_START_POINT-(good_prefix.size()+3);
    format_callback = [&msg, good_prefix, msg_startspace_len, &style] {
      fmt::print("{}\r", fmt::styled(
        fmt::format("[{}]:{}{}\n",
          good_prefix, STR(msg_startspace_len, ' '), msg),
        style
      ));
    };
  } else {
    format_callback = [&msg, &style] {
      fmt::print("{}\r", fmt::styled(
        fmt::format("{}{}\n",
          STR(MSG_START_POINT, ' '), msg),
        style
      ));
    };
  }

  PrintTimestamp(GetTimestamp());
  format_callback();
  std::cout.flush();
}

void ZE::Logger::DebugLog(CREF(STR) msg, CREF(ST::Color) fg_color) {
  RawPrint("debug", msg, fg_color, Colors::Blank);
}
void ZE::Logger::Information(CREF(STR) msg) {
  RawPrint("info", msg, Colors::White, Colors::Blank);
}
void ZE::Logger::Warning(CREF(STR) msg) {
  RawPrint("warn", msg, Colors::Yellow, Colors::Blank);
}
void ZE::Logger::Success(CREF(STR) msg) {
  RawPrint("success", msg, Colors::Lime, Colors::Blank);
}
void ZE::Logger::Error(CREF(STR) msg) {
  RawPrint("error", msg, Colors::Red, Colors::Blank);
}
// Also crashes the app.
void ZE::Logger::Critical(CREF(STR) msg) {
  RawPrint("crit", msg, Colors::Black, Colors::Red);
  std::exit(-1);
}


void ZE::Logger::Separator(CREF(STR) msg, const char sign) {
  Separator(Colors::Purple, msg, sign);
}
void ZE::Logger::Separator(CREF(ST::Color) fg_color, CREF(STR) msg, const char sign) {
  const size_t term_width = GetConsoleWidth();
  const STR space = msg.empty() ? "" : "  ";
  const size_t msg_len = msg.length();

  const STR timestamp = GetTimestamp();

  const int filler_len_raw = static_cast<int>(term_width) - (timestamp.size()+4) - static_cast<int>(msg_len) - static_cast<int>(space.length() * 2);
  const size_t filler_len = filler_len_raw > 0 ? filler_len_raw / 2 : 0;
  const STR filler(filler_len, sign);

  STR full_line = filler + space + msg + space + filler;
  if (full_line.length() < term_width) {
    full_line += sign;
  }

  PrintTimestamp(timestamp);
  fmt::print(
      fmt::fg(fmt::rgb(fg_color.rgba.red, fg_color.rgba.green, fg_color.rgba.blue)),
      "{}\n\r",
      full_line
    );
  std::cout.flush();
}
