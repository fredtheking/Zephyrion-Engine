#include "DetachedProcess.hpp"

void ZE::Low::DetachedProcess::Start() {
  m_Running = true;
  m_Worker = std::thread([this]{
    while (m_Running)
      e_Process();
  });
  m_Worker.detach();
}
void ZE::Low::DetachedProcess::Stop() {
  m_Running = false;
}

ZE::Low::DetachedProcess::DetachedProcess(VOID_FUNC_CONST event) {
  e_Process = event;
}


