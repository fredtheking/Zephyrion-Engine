#pragma once
#include "zephyrion/pch.hpp"
#include "zephyrion/utils/Macros.hpp"

namespace ZE::Low {
  class DetachedProcess final {
    private:
    //...
    public:
    void Start();
    void Stop();

    private:
    VOID_FUNC e_Process;
    public:
    std::atomic_bool m_Running = false;
    std::thread m_Worker;

    private:
    //...
    public:
    explicit DetachedProcess(VOID_FUNC_CONST action): e_Process(action){}
  };
}