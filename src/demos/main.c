#include <unistd.h>

#include "./demos.h"
#include "../cWicked.h"



int main(int argc, char** argv) {
  wi_arguments_parse(argc, argv);

  auto sdl_win = sdlInitAndCreateWindow("Ensuring up-to-date shaders for this PC, please wait a minute...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        960, 600, SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);


  wi_renderer_setShaderPath("../../.wi/.shaders/");
  wi_renderer_setShaderSourcePath("../../.wi/WickedEngine/shaders/");

  WiApplication app = wi_Application_new(nullptr, nullptr);
  wi_Application_setInfoDisplay(app, true, true, true, true, true, false, true, false, true, true, true, 22, false, nullptr);
  wi_Application_setWindow(app, sdl_win);
  wi_Application_initialize(app);
  wi_initializer_waitForInitializationsToFinish();

  auto game = wi_RenderPath3D_new(nullptr, nullptr, nullptr);
  wi_Application_activatePath(app, game, 0);
  SDL_SetWindowTitle(sdl_win, wi_version_getVersionString());
  //   app.SetFullScreen(true);

  sleep(11);
  sdlDispose(sdl_win);
  wi_RenderPath3D_dispose(game);
  wi_Application_dispose(app);
}
