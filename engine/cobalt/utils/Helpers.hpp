#pragma once
#include "cobalt/pch.hpp"

namespace Cobalt::Low::Helpers {
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
}
