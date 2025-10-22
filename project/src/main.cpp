#include <zephyrion/App.hpp>

#include "zephyrion/configs/ImguiConfig.hpp"

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(ZE::Configs::Builders::WindowConfigBuilder{}
      .Title("[Zephyrion Engine] example - Sandbox")
      .Position(ZE::Enums::WindowPosition::Centered)
      .Resizable()
      .Icon(ENGINE_ASSETS "icon.png")
      .Build(),
  ZE::Configs::Builders::ImguiConfigBuilder{}
      .Event([]{})
      .Build()
  );

  // Custom initialisation

  app.Run();

  // Custom termination

  app.Terminate();
}
