#include <cobalt/App.hpp>

int main(){
  DEFINE_APP_VARIABLE
  app.Setup(CE::Configs::Builders::WindowConfigBuilder{}
      .Title("Hello!")
      .Position(CE::Enums::WindowPosition::Centered)
      .DynamicFlags(CE::Enums::WindowDynamicFlags::Resizable |
        CE::Enums::WindowDynamicFlags::Fullscreen |
        CE::Enums::WindowDynamicFlags::AlwaysOnTop)
      .Size(1920, 1080)
      .InitFlags(CE::Enums::WindowInitFlags::HighPixelDensity |
                 CE::Enums::WindowInitFlags::OpenGL |
                 CE::Enums::WindowInitFlags::KeyboardFocused)
      .Build()
  );
  // Custom initialisation


  app.Run();
}
