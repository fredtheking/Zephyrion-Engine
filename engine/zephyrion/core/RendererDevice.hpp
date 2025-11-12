#pragma once
#include "zephyrion/pch.hpp"
#include "renderers/OpenGLHandler.hpp"
#include "renderers/VulkanHandler.hpp"
#include "renderers/MetalHandler.hpp"
#include "zephyrion/configs/WindowConfig.hpp"
#define RENDERER_VAR VAR(Renderers::OpenGLHandler, Renderers::VulkanHandler, Renderers::MetalHandler)

namespace ZE {
  class RendererDevice {
    //пумпумпумпумпумпумпум...

  private:
    //...
  public:
    // requires manual casting to "OpenGLHandler", "VulkanHandler" or "MetalHandler"
    [[nodiscard]] CREF(RENDERER_VAR) Get() const;
    // requires putting exact renderer chosen in "window_config" of linked window
    template<typename T>
    [[nodiscard]] T Get() const;

  private:
    RENDERER_VAR m_RenderHandler;
    CREF(Window) p_LinkedWindow;
  public:
    //...

  private:
    //...
  public:
    explicit RendererDevice(CREF(Window) window);
  };
}
