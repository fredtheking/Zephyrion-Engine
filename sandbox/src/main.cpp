#include <zephyrion/App.hpp>
#include <zephyrion/configs/ImguiConfig.hpp>

#include "zephyrion/utils/Util.hpp"

void ImGuiRenderProcess() {
  ImGui::ShowDemoWindow();

  ImGui::Begin("Testo");
  ImGui::Text("FPS: %f", GET_IMIO_SINGLETON.Framerate);
  ImGui::End();
}

int main(){
  ZE::Util::LogVersion();

  DEFINE_APP_VARIABLE
  app.Create(ZE::Configs::Builders::WindowConfigBuilder{}
    .Title("[Zephyrion Engine] example - Sandbox")
    .Position(ZE::Enums::ZE_WindowPosition::Centered)
    .Resizable()
    .Size(1920, 1080)
    .EnableImGui(ZE::Configs::Builders::ImguiConfigBuilder{}
      .Process(ImGuiRenderProcess)
      .FloatingWindows()
      .Build()
    )
    .Icon(ENGINE_ASSETS "icon.png")
    //TODO: Add 'exit key' option
    .Build()
  );

  // Custom initialisation

  app.Run();

  // Custom termination

  app.Terminate();
}
