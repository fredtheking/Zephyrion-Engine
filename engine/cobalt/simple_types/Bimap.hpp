#pragma once
#include "cobalt/pch.hpp"

namespace CE::ST {
  template<typename T1, typename T2>
  class Bimap {
  private:
    //...
  public:
    void Insert(const T1& a, const T2& b) {
      forward[a] = b;
      backward[b] = a;
    }

  private:
    //...
  public:
    std::unordered_map<T1, T2> forward;
    std::unordered_map<T2, T1> backward;

    const T2& operator[](const T1& key) const {
      auto it = forward.find(key);
      if (it == forward.end()) throw std::out_of_range("no such key in forward");
      return it->second;
    }

    const T1& operator[](const T2& key) const {
      auto it = backward.find(key);
      if (it == backward.end()) throw std::out_of_range("no such key in backward");
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