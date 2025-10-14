#include "DetachedProcess.hpp"

void CE::Low::DetachedProcess::Start() {
  m_Running = true;
  m_Worker = std::thread([this]{
    while (m_Running)
      e_Process();
  });
  m_Worker.detach();
}
void CE::Low::DetachedProcess::Stop() {
  m_Running = false;
}


