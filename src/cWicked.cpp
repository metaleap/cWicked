#include "../pch/wi_pch.h"

#include "cWicked.h"


void wi_sdl2_dispose() {
  SDL_Quit();
}


SDL_Window* wi_sdl2_init_and_create_window(const char* winTitle, int winX, int winY, int winWidth, int winHeight, Uint32 winFlags) {
  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Failed to init SDL2: %s", SDL_GetError());
    wi_sdl2_dispose();
    exit(1);
  }

  auto sdl_win = sdl2::make_window(winTitle, winX, winY, winWidth, winHeight, winFlags);
  if (!sdl_win) {
    fprintf(stderr, "Failed to create SDL2 window: %s", SDL_GetError());
    wi_sdl2_dispose();
    exit(1);
  }

  return sdl_win.release();
}
