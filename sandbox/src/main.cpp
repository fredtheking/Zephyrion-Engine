#include <zephyrion/App.hpp>

#include "zephyrion/configs/ImguiConfig.hpp"

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(ZE::Configs::Builders::WindowConfigBuilder{}
      .Title("[Zephyrion Engine] example - Sandbox")
      .Position(ZE::Enums::ZE_WindowPosition::Centered)
      .Resizable()
      .Size(1220, 720)
      .NoVsync()
      .EnableImGui(ZE::Configs::Builders::ImguiConfigBuilder{}
        .Process([] {
          ImGui::ShowDemoWindow();

          ImGui::Begin("Testo");
          ImGui::Text("FPS: %f", GET_IO_SINGLETON.Framerate);
          ImGui::End();
        })
        .Build()
      )
      .Icon(ENGINE_ASSETS "icon.png")
      .Build()
  );

  // Custom initialisation

  app.Run();

  // Custom termination

  app.Terminate();
}
