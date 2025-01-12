#pragma once

#include <SDL2/SDL_video.h>


#ifdef __cplusplus
extern "C" {
#endif
/// C-only API:


void wi_sdl2_dispose(void);
SDL_Window* wi_sdl2_init_and_create_window(const char* winTitle, int winX, int winY, int winWidth, int winHeight, Uint32 winFlags);


///
#ifdef __cplusplus
} // extern "C"
#endif
