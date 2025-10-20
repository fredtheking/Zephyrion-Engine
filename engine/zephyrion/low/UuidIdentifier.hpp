#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/utils/Util.hpp"

namespace ZE::Low {
  class UuidIdentifier {
  public:
    const uuids::uuid UUID = Util::UUIDs::Create();
  };
}