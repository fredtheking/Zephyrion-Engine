#include "OpenGLHandler.hpp"

namespace ZE::Renderers {
  OpenGLHandler::OpenGLHandler(CREF(Window) window) {
    if (window.p_Config->GetImGuiConfig()) {
      m_Imgui = MAKE_UPTR(ImGuiHandler<OpenGLHandler>)(window);
    }
  }
  OpenGLHandler::~OpenGLHandler() {

  }

}