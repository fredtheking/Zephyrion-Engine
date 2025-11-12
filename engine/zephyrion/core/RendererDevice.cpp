#include "RendererDevice.hpp"
#include "Window.hpp"

namespace ZE {
  CREF(RENDERER_VAR) RendererDevice::Get() const {
    return m_RenderHandler;
  }
  template<typename T>
  T RendererDevice::Get() const {
    return std::get<T>(m_RenderHandler);
  }

  RendererDevice::RendererDevice(CREF(Window) window)
    : p_LinkedWindow(window) {
    BACKEND_CALL(p_LinkedWindow.p_Config->GetBackendRenderer(),
      m_RenderHandler = Renderers::OpenGLHandler{},
      m_RenderHandler = Renderers::VulkanHandler{},
      m_RenderHandler = Renderers::MetalHandler{}
    )
  }
}
