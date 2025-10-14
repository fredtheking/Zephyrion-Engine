#pragma once
#include "cobalt/pch.hpp"
#include "cobalt/utils/Helpers.hpp"

namespace CE::Low {
  class UuidIdentifier {
  public:
    const uuids::uuid UUID = Helpers::UUIDs::Create();
  };
}