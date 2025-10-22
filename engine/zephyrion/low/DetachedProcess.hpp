#pragma once
#include "zephyrion/pch.hpp"

namespace ZE::Low {
  class DetachedProcess final {
    private:
    //...
    public:
    void Start(VOID_FUNC_CONST before_loop = nullptr, VOID_FUNC_CONST at_loop_begin = nullptr, VOID_FUNC_CONST at_loop_end = nullptr, VOID_FUNC_CONST after_loop = nullptr);
    void Stop();

    private:
    VOID_FUNC e_Process;
    public:
    std::atomic_bool m_Running = false;
    std::thread m_Worker;

    private:
    //...
    public:
    DetachedProcess(VOID_FUNC_CONST event);
    DetachedProcess(CREF(DetachedProcess)) = default;
  };
}