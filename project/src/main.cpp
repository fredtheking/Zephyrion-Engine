#include <cobalt/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(CE::Configs::Builders::WindowConfigBuilder{}
      .Title("Hello!")
      .Position(CE::Enums::WindowPosition::Centered)
      .Size(540, 1080)
      .BackendRenderer(CE::Enums::BackendRenderer::OpenGL)
      .Build()
  );

  // Custom initialisation

  app.Run();
}
