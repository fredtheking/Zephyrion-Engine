#include <zephyrion/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(ZE::Configs::Builders::WindowConfigBuilder{}
      .Title("[Zephyrion Engine] example - Sandbox")
      .Position(ZE::Enums::WindowPosition::Centered)
      .Resizable()
      .Icon("assets/icon.png")
      .Build()
  );

  // Custom initialisation

  app.Run();

  // Custom termination

  app.Terminate();
}
