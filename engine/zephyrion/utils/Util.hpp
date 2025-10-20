#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/core/Logger.hpp"
#include "translations/EnumTranslations.hpp"

namespace ZE::Util {
  inline bool Assert(
    const bool condition,
    CREF(std::string) fail_msg,
    CREF(std::string) success_msg = "",
    const bool crash = false,
    CREF(std::function<void()>) on_success = nullptr,
    CREF(std::function<void()>) on_fail = nullptr)
  {
    if (!condition) {
      if (!fail_msg.empty()) {
        if (crash) Logger::Critical(fail_msg);
        else       Logger::Error(fail_msg);
      }
      if (on_fail) on_fail();
      return false;
    }

    if (on_success) on_success();
    if (!success_msg.empty()) Logger::Success(success_msg);
    return true;
  }

  inline bool AssertSDL(
    const bool condition,
    CREF(std::string) fail_msg,
    CREF(std::string) success_msg = "",
    const bool crash = false,
    CREF(std::function<void()>) on_success = nullptr,
    CREF(std::function<void()>) on_fail = nullptr)
  {
    return Assert(condition, fail_msg + ": " + SDL_GetError(), success_msg, crash, on_success, on_fail);
  }

  namespace Update {
    inline std::chrono::time_point<std::chrono::steady_clock> last_frame = std::chrono::steady_clock::now();

    inline long double GetDeltaTime() {
      const auto now = std::chrono::steady_clock::now();
      const double delta = std::chrono::duration<double>(now - last_frame).count();
      last_frame = now;
      return delta;
    }
  }
  namespace Render {
    inline std::chrono::time_point<std::chrono::steady_clock> last_frame = std::chrono::steady_clock::now();

    inline long double GetDeltaTime() {
      const auto now = std::chrono::steady_clock::now();
      const double delta = std::chrono::duration<double>(now - last_frame).count();
      last_frame = now;
      return delta;
    }
  }
  namespace Window {

  }
  namespace UUIDs {
    inline uuids::uuid Create() {
      std::random_device rd;
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::ranges::generate(seed_data, std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      std::mt19937 generator(seq);
      uuids::uuid_random_generator gen{generator};

      return gen();
    }
  }
  namespace String {
    inline std::string ApplyToEachChar(std::string msg, CREF(FUNC(UINT8(UINT8))) func) {
      std::ranges::transform(msg, msg.begin(),
        [func](const UINT8 c) { return static_cast<char>(func(c)); });
      return msg;
    }
    inline std::string ToUpper(std::string msg) {
      return ApplyToEachChar(std::move(msg), toupper);
    }
    inline std::string ToUpper(const char* msg) {
      return ToUpper(std::string(msg));
    }
    inline std::string ToLower(std::string msg) {
      return ApplyToEachChar(std::move(msg), tolower);
    }
    inline std::string ToLower(const char* msg) {
      return ToUpper(std::string(msg));
    }
  }
  namespace Loaders {
    inline SDL_Surface* PNGtoSurface(CREF(std::string) filepath, const SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA8888) {
      if (!Assert(std::filesystem::exists(filepath), "Failed to load: File not found at \"" + filepath + "\"."))
        return nullptr;

      int width, height;
      unsigned char* data = stbi_load(filepath.c_str(), &width, &height, nullptr, 4); // force RGBA

      if (!Assert(data, "Failed to load image: Unknown issue."))
        return nullptr;

      SDL_Surface* surf = SDL_CreateSurface(width, height, format);

      if (!Assert(surf, "Failed to load image: Unable to create \"SDL_Surface\".", "", false,
        [&surf, &data, &width, &height, &filepath] {
        std::memcpy(surf->pixels, data, static_cast<size_t>(width) * height * 4);
        stbi_image_free(data);
        Logger::Success("Loaded image successfully: at path \"" + filepath + "\" as R8G8B8A8");
      }, [&data] {
        stbi_image_free(data);
      }))
        return nullptr;
      return surf;
    }
  }
  namespace Enums {
    inline std::string ToString(const SDL_WindowFlags flags) {
      std::string out;
      for (auto& [val, name] : Translations::Enums::Translation__SDL_WindowFlags.forward) {
        if (flags & val) {
          if (!out.empty()) out += " | ";
          out += name;
        }
      }
      return out.empty() ? "SDL_WINDOW_NONE" : out;
    }
  }
}
