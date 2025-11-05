#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/core/Logger.hpp"

namespace ZE::ST {
  template<typename T1, typename T2>
  class Bimap {
  private:
    //...
  public:
    void Insert(CREF(T1) a, CREF(T2) b) {
      forward[a] = b;
      backward[b] = a;
    }

  private:
    //...
  public:
    std::unordered_map<T1, T2> forward;
    std::unordered_map<T2, T1> backward;

    CREF(T2) operator[](CREF(T1) key) const {
      auto it = forward.find(key);
      if (it == forward.end()) Logger::Critical("No such key in \"forward\" map.");
      return it->second;
    }

    CREF(T1) operator[](CREF(T2) key) const {
      auto it = backward.find(key);
      if (it == backward.end()) Logger::Critical("No such key in \"backward\" map.");
      return it->second;
    }

  private:
    //...
  public:
    Bimap(std::initializer_list<std::pair<T1, T2>> list) {
      for (auto& p : list) {
        Insert(p.first, p.second);
      }
    }
  };
}
