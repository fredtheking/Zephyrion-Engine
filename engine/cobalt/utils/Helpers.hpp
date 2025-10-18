#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/core/Logger.hpp"
#include "cobalt/utils/Enums.hpp"
#include "translations/EnumTranslations.hpp"

namespace CE::Helpers {
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
    inline SDL_Surface* PNGtoSurface(CREF(std::string) filepath) {
      int width, height;
      unsigned char* data = stbi_load(filepath.c_str(), &width, &height, nullptr, 4); // force RGBA
      if (!data) {
        Logger::Error("Failed to load '" + filepath + "' image as 'R8G8B8A8'");
        return nullptr;
      }

      SDL_Surface* surf = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);
      if (!surf) {
        stbi_image_free(data);
        Logger::Error("Failed to create 'SDL_Surface' from path '" + filepath + "'");
        return nullptr;
      }

      std::memcpy(surf->pixels, data, static_cast<size_t>(width) * height * 4);
      stbi_image_free(data);
      Logger::Success("Loaded 'R8G8B8A8' image - " + filepath);

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
