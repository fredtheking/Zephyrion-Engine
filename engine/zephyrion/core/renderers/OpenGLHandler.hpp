#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/core/Window.hpp"

//TODO: implementing... (WIP)
namespace ZE::Renderers {
  class OpenGLHandler {
  private:
    //...
  public:
    //...

  private:
    //...
  public:
    OPT(UPTR(ImGuiHandler<Renderers::OpenGLHandler>)) m_Imgui = NULLOPT;
    SDL_GLContext m_GLContext = nullptr;

  private:
    //...
  public:
    explicit OpenGLHandler(CREF(Window) window);
    ~OpenGLHandler();
  };
}