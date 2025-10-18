#include <cobalt/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(CE::Configs::Builders::WindowConfigBuilder{}
      .Title("Hello!")
      .Position(CE::Enums::WindowPosition::Centered)
      .Size(1920, 1080)
      .Build()
  );

  // Custom initialisation

  app.Run();
}
