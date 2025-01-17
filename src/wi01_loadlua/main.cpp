#include "../../pch/wi_pch.h"


wi::Application app = wi::Application();


int main(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("Updating shaders, please wait a minute...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  auto hwnd = sdl_win.get();
  app.SetWindow(hwnd);
  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");
  app.Initialize();

  bool ran = false;
  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              quit = true;
              break;
            case SDL_WINDOWEVENT_RESIZED:
              app.SetWindow(app.window);
              break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
              app.is_window_active = false;
              break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
              app.is_window_active = true;
              break;
          }
          break;
      }
      wi::input::sdlinput::ProcessEvent(event);
    }

    app.Run();
    if (wi::initializer::IsInitializeFinished() && (!ran)) {
      ran = true;
      SDL_SetWindowTitle(hwnd, wi::version::GetVersionString());
      SDL_SetWindowFullscreen(hwnd, SDL_WINDOW_FULLSCREEN_DESKTOP);
      wi::lua::RunFile("../../.wi/Content/scripts/character_controller/character_controller.lua");
    }
  }

  SDL_DestroyWindow(hwnd);
  SDL_Quit();
  return 0;
}
