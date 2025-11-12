#pragma once
#include "zephyrion/core/renderers/MetalHandler.hpp"
#include "zephyrion/core/renderers/OpenGLHandler.hpp"
#include "zephyrion/core/renderers/VulkanHandler.hpp"

namespace ZE::Unions {
  union RendererHandler {
    OpenGLRenderer gl;
    VulkanRenderer vk;
    MetalRenderer mtl;
  };
}
