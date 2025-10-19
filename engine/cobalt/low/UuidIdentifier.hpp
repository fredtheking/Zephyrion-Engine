#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/utils/Util.hpp"

namespace CE::Low {
  class UuidIdentifier {
  public:
    const uuids::uuid UUID = Util::UUIDs::Create();
  };
}