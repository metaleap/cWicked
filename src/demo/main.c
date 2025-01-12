#include <unistd.h>

#include "../cWicked.h"



int main(int argc, char** argv) {
  auto sdl_win = wi_sdl2_init_and_create_window("Hallöchen!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                                SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  wi_tmp_main(sdl_win, argc, argv);
  wi_sdl2_dispose(sdl_win);
}
