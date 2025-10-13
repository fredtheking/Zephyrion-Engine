#include "Logger.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

#include "cobalt/utils/Helpers.hpp"
#include "cobalt/utils/Macros.hpp"
#include "engine/managers/TerminalManager.hpp"

std::vector<std::string> oncers = {};

void Logger::RawPrint(const std::string &prefix, const std::string &msg, EConsoleColor fg_color, EConsoleColor bg_color, bool once) {
  std::string new_msg = msg;

  if (!std::ranges::contains(oncers, msg)) {
    std::cout << Low::Helpers::String::ToUpper(msg) << ": " << new_msg << "\n";
  }

  if (once)
    oncers.push_back(msg);
}

void Logger::DebugLog(const std::string &msg, const EConsoleColor& fg_color, const bool& once) {
  RawPrint("debug", msg, fg_color, EConsoleColor::Black, once);
}
void Logger::Information(const std::string &msg, const bool& once) {
  RawPrint("info", msg, EConsoleColor::White, EConsoleColor::Blank, once);
}
void Logger::Warning(const std::string &msg, const bool& once) {
  RawPrint("warn", msg, EConsoleColor::Yellow, EConsoleColor::Blank, once);
}
void Logger::Error(const std::string &msg, const bool& once) {
  RawPrint("error", msg, EConsoleColor::Red, EConsoleColor::Blank, once);
}
// Also crashes the game.
void Logger::Critical(const std::string &msg, const bool& once) {
  RawPrint("crit", msg, EConsoleColor::Black, EConsoleColor::Red, once);
  std::abort();
}


void Logger::Separator(const std::string& msg, const char& sign) {
  Separator(EConsoleColor::Purple, msg, sign);
}
void Logger::Separator(const EConsoleColor& fg_color, const std::string& msg, const char& sign) {
  const size_t term_width = TerminalManager::GetWidth();
  const std::string space = msg.empty() ? "" : "  ";
  const size_t msg_len = msg.length();

  if (msg_len + space.length() * 2 >= term_width) {
    std::cout << TerminalManager::ToFgColor(fg_color, msg) << "\n";
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
