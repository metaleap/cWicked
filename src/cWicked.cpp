#include "../pch/wi_pch.h"

#include "cWicked.h"




void wi_tmp_main(SDL_Window* win, int argc, char** argv) {
  wi::Application app {};
  wi::arguments::Parse(argc, argv);
#ifdef WickedEngine_SHADER_DIR
  wi::renderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
#endif

  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  app.infoDisplay.active = true;
  app.infoDisplay.colorspace = true;
  app.infoDisplay.device_name = true;
  app.infoDisplay.fpsinfo = true;
  app.infoDisplay.heap_allocation_counter = false;
  app.infoDisplay.logical_size = false;
  app.infoDisplay.pipeline_count = true;
  app.infoDisplay.pipeline_creation = true;
  app.infoDisplay.resolution = true;
  app.infoDisplay.vram_usage = true;
  app.infoDisplay.watermark = true;

  app.SetWindow(win);
  app.Initialize();
  wi::initializer::WaitForInitializationsToFinish();

  auto game = wi::RenderPath3D {};
  app.ActivatePath(&game);
  SDL_SetWindowTitle(win, wi::version::GetVersionString());
  app.SetFullScreen(true);
}
