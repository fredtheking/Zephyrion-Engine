#pragma once
#include "cobalt/pch.hpp"

namespace CE::Low {
  template <typename T>
  class BuilderBase {
  protected:
    T build_object{};
  public:
    virtual void ValidityCheck() = 0;
    virtual T Build() { ValidityCheck(); return std::move(build_object); }

    BuilderBase() = default;
    virtual ~BuilderBase() = default;
  };
}