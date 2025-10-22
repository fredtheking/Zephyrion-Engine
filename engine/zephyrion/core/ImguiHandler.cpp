#include "ImguiHandler.hpp"

ZE::ImguiHandler::ImguiHandler(REF(Configs::ImguiConfig) imgui_config)
: p_Config(imgui_config)
, e_ImguiProcess(p_Config.process_event) {
  e_ImguiProcess.Start();
}
ZE::ImguiHandler::~ImguiHandler() {
  e_ImguiProcess.Stop();
}
