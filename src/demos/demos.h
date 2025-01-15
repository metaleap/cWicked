#pragma once

#include <SDL2/SDL.h>

#include "../cwicked.h"


void sdlDispose(SDL_Window* winToDestroyIfAny) {
  if (winToDestroyIfAny != nullptr)
    SDL_DestroyWindow(winToDestroyIfAny);
  SDL_Quit();
}


SDL_Window* sdlInitAndCreateWindow(const char* winTitle, int winX, int winY, int winWidth, int winHeight, Uint32 winFlags) {
  if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Failed to init SDL2: %s", SDL_GetError());
    sdlDispose(nullptr);
    exit(1);
  }

  SDL_Window* sdl_win = SDL_CreateWindow(winTitle, winX, winY, winWidth, winHeight, winFlags);
  if (sdl_win == nullptr) {
    fprintf(stderr, "Failed to create SDL2 window: %s", SDL_GetError());
    sdlDispose(nullptr);
    exit(1);
  }
  return sdl_win;
}
