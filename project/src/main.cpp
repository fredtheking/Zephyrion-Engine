#include <cobalt/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(CE::Configs::Builders::WindowConfigBuilder{}
      .Title("[Cobalt Engine] example - Basic Window")
      .Position(CE::Enums::WindowPosition::Centered)
      .Resizable()
      .Icon("assets/icon.png")
      .Build()
  );

  // Custom initialisation

  app.Run();
  app.Shutdown();
}
