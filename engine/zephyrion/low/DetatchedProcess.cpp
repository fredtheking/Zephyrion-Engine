#include "DetachedProcess.hpp"

namespace ZE::Low {
  void DetachedProcess::Start(VOID_FUNC_CONST before_loop, VOID_FUNC_CONST at_loop_begin, VOID_FUNC_CONST at_loop_end, VOID_FUNC_CONST after_loop) {
    m_Running = true;
    m_Worker = std::thread([this, &before_loop, &at_loop_begin, &at_loop_end, &after_loop]{
      if (before_loop) before_loop();
      while (m_Running) {
        if (at_loop_begin) at_loop_begin();
        e_Process();
        if (at_loop_end) at_loop_end();
      }
      if (after_loop) after_loop();
    });
    m_Worker.detach();
  }
  void DetachedProcess::Stop() {
    m_Running = false;
  }

  DetachedProcess::DetachedProcess(VOID_FUNC_CONST event) {
    e_Process = event;
  }
}