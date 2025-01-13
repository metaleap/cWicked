#pragma once

#include <SDL2/SDL_video.h>


#ifdef __cplusplus
extern "C" {
#endif
/// C-only API:



void wi_sdl2_dispose(SDL_Window* winToDestroyIfAny);
SDL_Window* wi_sdl2_init_and_create_window(const char* winTitle, int winX, int winY, int winWidth, int winHeight, Uint32 winFlags);
void wi_tmp_main(SDL_Window* win, int argc, char** argv);

typedef struct SwigObj_wi_Application wi_Application;
void wi_Application_infoDisplay(wi_Application* wiApp, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int size,
                                bool colorGradingHelper);

///
#ifdef __cplusplus
} // extern "C"
#endif
