#pragma once

#include <SDL2/SDL.h>

#include "./copied.h"



#ifdef __cplusplus
extern "C" {
#endif
/// C-only API:



const char* wi_version_getVersionString();
const char* wi_version_getCreditsString();
int wi_version_getMajor();
int wi_version_getMinor();
int wi_version_getRevision();



void wi_arguments_parse(int argc, char** argv);



void wi_initializer_waitForInitializationsToFinish();
void wi_initializer_initializeComponentsAsync();
void wi_initializer_initializeComponentsImmediate();
bool wi_initializer_isInitializeFinished(WI_INITIALIZED_SYSTEM system);



void wi_input_sdlInput_processEvent(SDL_Event* evt);



void wi_renderer_setShaderPath(char* path);
void wi_renderer_setShaderSourcePath(char* path);
typedef void* WiRenderPath2D;
typedef void* WiRenderPath3D;
typedef void (*WiRenderPathOnFixedUpdate)(void* ctx);
typedef void (*WiRenderPathOnUpdate)(void* ctx, float);
WiRenderPath3D wi_RenderPath3D_new(void* ctx, WiRenderPathOnFixedUpdate onFixedUpdate, WiRenderPathOnUpdate onUpdate);
void wi_RenderPath3D_dispose(WiRenderPath3D app);



WiViewport wi_graphics_Viewport(float top_left_x, float top_left_y, float width, float height, float min_depth, float max_depth);
WiRect wi_graphics_Rect(int32_t left, int32_t top, int32_t right, int32_t bottom);
void wi_graphics_Rect_fromViewport(WiRect* rect, WiViewport* viewport);



typedef void* WiApplication;
typedef void (*WiApplicationOnFixedUpdate)(void);
typedef void (*WiApplicationOnUpdate)(float);
WiApplication wi_Application_new(WiApplicationOnFixedUpdate onFixedUpdate, WiApplicationOnUpdate onUpdate);
void wi_Application_dispose(WiApplication app);
void wi_Application_setInfoDisplay(WiApplication app, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                   bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                   bool colorGradingHelper, WiRect* rect);
void wi_Application_setWindow(WiApplication app, SDL_Window* window);
void wi_Application_initialize(WiApplication app);
void wi_Application_activatePath(WiApplication app, WiRenderPath3D renderPath, float fadeSeconds);
void wi_Application_setFullScreen(WiApplication app, bool fullscreen);
void wi_Application_run(WiApplication app);
bool wi_Application_get_isWindowActive(WiApplication app);
void wi_Application_set_isWindowActive(WiApplication app, bool set);











///
#ifdef __cplusplus
} // extern "C"
#endif
