#include <unistd.h>

#include "../cWicked.h"



int main() {
  auto sdl_win = wi_sdl2_init_and_create_window("Hola Mondo!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                                SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  sleep(11);
  SDL_DestroyWindow(sdl_win);
  wi_sdl2_dispose();
}
