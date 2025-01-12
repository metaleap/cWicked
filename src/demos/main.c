#include "./demos.h"
#include <unistd.h>


int main(int argc, char** argv) {


  auto sdl_win = sdlInitAndCreateWindow("Halloechen!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                        SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

  sleep(11);
  sdlDispose(sdl_win);
}
