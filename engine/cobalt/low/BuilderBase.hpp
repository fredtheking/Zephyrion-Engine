#pragma once
#include "cobalt/pch.hpp"

namespace CE::Low {
  template <typename T>
  class BuilderBase {
  protected:
    T build_object{};
  public:
    virtual T Build() = 0;

    BuilderBase() = default;
    virtual ~BuilderBase() = default;
  };
}