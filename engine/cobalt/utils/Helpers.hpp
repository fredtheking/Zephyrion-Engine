#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/core/Logger.hpp"
#include "cobalt/utils/Enums.hpp"

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


  inline SDL_WindowFlags Translate(const Enums::WindowInitFlags window_init_flags) {
    SDL_WindowFlags flags = {};
    #define FLAG_ADD(NAME) \
      if ((window_init_flags & Enums::WindowInitFlags::NAME) == Enums::WindowInitFlags::NAME) \
        flags |= static_cast<SDL_WindowFlags>(Enums::WindowInitFlags::NAME);

    FLAG_ADD(OpenGL)
    FLAG_ADD(Vulkan)
    FLAG_ADD(Metal)
    FLAG_ADD(Transparent)
    FLAG_ADD(Occluded)
    FLAG_ADD(External)
    FLAG_ADD(Modal)
    FLAG_ADD(Utility)
    FLAG_ADD(Tooltip)
    FLAG_ADD(PopupMenu)
    FLAG_ADD(HighPixelDensity)
    FLAG_ADD(MouseGrabbed)
    FLAG_ADD(MouseCapture)
    FLAG_ADD(MouseRelativeMode)
    FLAG_ADD(MouseFocus)
    FLAG_ADD(KeyboardFocused)
    FLAG_ADD(InputFocus)
    FLAG_ADD(NotFocusable)

    #undef FLAG_ADD
    return flags;
  }


  template <typename T>
  requires std::is_scoped_enum_v<T>
  std::string ToString(T bitmask_enum) {
    std::string result;

    for (auto value : magic_enum::enum_values<T>())
      if ((bitmask_enum ^ value) && (value != T::None)) {
        if (!result.empty()) result += " | ";
        result += std::string(magic_enum::enum_name(value));
      }

    if (result.empty())
      result = "None";

    return result;
  }

  template <typename T>
  requires (!std::is_scoped_enum_v<T> && std::is_enum_v<T>)
  std::string ToString(T bitmask_enum) {
    using U = std::underlying_type_t<T>;
    std::string result;

    for (auto value : magic_enum::enum_values<T>()) {
      if ((static_cast<U>(bitmask_enum) & static_cast<U>(value)) && static_cast<U>(value) != 0) {
        if (!result.empty()) result += " | ";
        result += std::string(magic_enum::enum_name(value));
      }
    }

    if (result.empty())
      result = "None";

    return result;
  }
}
