#include "../pch/wi_pch.h"

#include "cWicked.h"


wi::Application app {};


void wi_sdl2_dispose(SDL_Window* winToDestroyIfAny) {
  if (winToDestroyIfAny != nullptr)
    SDL_DestroyWindow(winToDestroyIfAny);
  SDL_Quit();
}


SDL_Window* wi_sdl2_init_and_create_window(const char* winTitle, int winX, int winY, int winWidth, int winHeight, Uint32 winFlags) {
  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Failed to init SDL2: %s", SDL_GetError());
    wi_sdl2_dispose(nullptr);
    exit(1);
  }

  auto sdl_win = sdl2::make_window(winTitle, winX, winY, winWidth, winHeight, winFlags);
  if (!sdl_win) {
    fprintf(stderr, "Failed to create SDL2 window: %s", SDL_GetError());
    wi_sdl2_dispose(nullptr);
    exit(1);
  }

  return sdl_win.release();
}


void wi_tmp_main(SDL_Window* win, int argc, char** argv) {
  wi::arguments::Parse(argc, argv);
#ifdef WickedEngine_SHADER_DIR
  wi::renderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
#endif

  wi::renderer::SetShaderPath("../../.cache/.shaders/");
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
