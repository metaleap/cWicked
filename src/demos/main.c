#include <unistd.h>

#include "./demos.h"
#include "src/cwicked.h"




WiApplication app;
WiRenderPath3D game;

void mainLoop(SDL_Window* sdlWin);

void onAppInitialize() {
  WiRenderPath3D_init(game, WiApplication_get_window(app));
  WiRenderPath3D_load(game);
  WiApplication_activatePath(app, game, 1);
}



int main(int argc, char** argv) {
  wi_arguments_parse(argc, argv);

  auto sdl_win = sdlInitAndCreateWindow("Ensuring up-to-date shaders for this PC, please wait a minute...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        960, 600, SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);


  wi_renderer_setShaderPath("../../.wi/.shaders/");
  wi_renderer_setShaderSourcePath("../../.wi/WickedEngine/shaders/");

  app = WiApplication_new();
  WiApplication_setInfoDisplay(app, true, true, true, true, true, false, true, false, true, true, true, 22, false, nullptr);
  WiApplication_setWindow(app, sdl_win);
  WiApplication_on(app, WI_ON_APP_INITIALIZE, onAppInitialize);
  game = WiRenderPath3D_new();
  // WiApplication_initialize(app);
  // wi_initializer_waitForInitializationsToFinish();

  SDL_SetWindowTitle(sdl_win, wi_version_getVersionString());
  // WiApplication_setFullScreen(app, true);
  mainLoop(sdl_win);

  sdlDispose(sdl_win);
}

void mainLoop(SDL_Window* sdlWin) {
  bool quit = false;
  SDL_Event sdl_evt;

  // bool ran = false;
  while (!quit) {
    // if (!ran) {
    //   ran = true;
    //   wi::lua::RunFile(std::string(engineDirPath) + "/Content/scripts/character_controller/character_controller.lua");
    // }

    while ((SDL_PollEvent(&sdl_evt) == 1) && !quit) {
      switch (sdl_evt.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_WINDOWEVENT:
          switch (sdl_evt.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              quit = true;
              break;
              // case SDL_WINDOWEVENT_FOCUS_LOST:
              //   WiApplication_set_isWindowActive(app, false);
              //   break;
              // case SDL_WINDOWEVENT_FOCUS_GAINED:
              //   WiApplication_set_isWindowActive(app, true);
              //   break;
              // case SDL_WINDOWEVENT_SIZE_CHANGED:
              // case SDL_WINDOWEVENT_RESIZED:
              //   WiApplication_setWindow(app, sdlWin);
              //   break;
          }
          break;
        default:
          break;
      }
      wi_input_sdlInput_processEvent(&sdl_evt);
    }
    WiApplication_run(app);
  }
}
