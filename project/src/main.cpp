#include <cobalt/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(CE::Configs::Builders::WindowConfigBuilder{}
      .Title("Hello!")
      .Position(10, 10)
      .Size(1280, 720)
      .Build()
  );

  app.Run();
}
