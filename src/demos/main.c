#include "./demos.h"
#include <unistd.h>


int main(int argc, char** argv) {
  wi_arguments_Parse(argc, argv);

  char title[123];
  sprintf(title, "Halloyo: %s", wi_version_GetVersionString());
  auto sdl_win = sdlInitAndCreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                        SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

  sleep(4);
  sdlDispose(sdl_win);
}
