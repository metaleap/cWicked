#include <unistd.h>

#include "./demos.h"



int main(int argc, char** argv) {
  char title[123];
  sprintf(title, "Halloyo: %s", wi_version_GetVersionString());
  auto sdl_win = sdlInitAndCreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                        SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);



  wi_arguments_Parse(argc, argv);
  wi_renderer_SetShaderSourcePath("../../.wi/WickedEngine/shaders/");
  wi_renderer_SetShaderPath("../../.wi/.shaders/");

  auto app = wi_Application_new();
  wi_Application_infoDisplay(app, true, true, true, true, true, false, true, false, true, true, true, 22, false);
  wi_Application_SetWindow(app, (SWIGTYPE_p_wi__platform__window_type*)sdl_win);
  wi_Application_Initialize(app);
  wi_initializer_WaitForInitializationsToFinish();



  sleep(22);
  sdlDispose(sdl_win);
}
