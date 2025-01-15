#include <unistd.h>

#include "./demos.h"



void upd(float dt) {
  printf("APP>%g\n", dt);
}

void updRp(void* _, float dt) {
  printf("RP>>%g\n", dt);
}

void mainLoop(WiApplication app, SDL_Window* sdlWin);

int main(int argc, char** argv) {
  wi_arguments_parse(argc, argv);

  auto sdl_win = sdlInitAndCreateWindow("Ensuring up-to-date shaders for this PC, please wait a minute...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        960, 600, SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);


  wi_renderer_setShaderPath("../../.wi/.shaders/");
  wi_renderer_setShaderSourcePath("../../.wi/WickedEngine/shaders/");

  WiApplication app = wi_Application_new(nullptr, upd);
  wi_Application_setInfoDisplay(app, true, true, true, true, true, false, true, false, true, true, true, 22, false, nullptr);
  wi_Application_setWindow(app, sdl_win);
  wi_Application_initialize(app);
  wi_initializer_waitForInitializationsToFinish();

  auto game = wi_RenderPath3D_new(nullptr, nullptr, nullptr);
  wi_Application_activatePath(app, game, 0);
  SDL_SetWindowTitle(sdl_win, wi_version_getVersionString());
  // wi_Application_setFullScreen(app, true);
  mainLoop(app, sdl_win);

  sdlDispose(sdl_win);
  wi_RenderPath3D_dispose(game);
  wi_Application_dispose(app);
}

void mainLoop(WiApplication app, SDL_Window* sdlWin) {
  bool quit = false;
  SDL_Event sdl_evt;

  // bool ran = false;
  while (!quit) {
    SDL_PumpEvents();
    wi_Application_run(app);

    // if (!ran) {
    //   ran = true;
    //   wi::lua::RunFile(std::string(engineDirPath) + "/Content/scripts/character_controller/character_controller.lua");
    // }

    while ((SDL_PollEvent(&sdl_evt) == 1) && !quit)
      switch (sdl_evt.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_WINDOWEVENT:
          switch (sdl_evt.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              quit = true;
              break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
              wi_Application_set_isWindowActive(app, false);
              break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
              wi_Application_set_isWindowActive(app, true);
              break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            case SDL_WINDOWEVENT_RESIZED:
              wi_Application_setWindow(app, sdlWin);
              break;
          }
          break;
        default:
          wi_input_sdlInput_processEvent(&sdl_evt);
          break;
      }
  }
}
