#pragma once

#include "./copied.h"



#ifdef __cplusplus
extern "C" {
#endif



/// own stuff:


typedef enum WI_ON {
  WI_ON_APP_INITIALIZE,
  WI_ON_RENDERPATH_LOAD,
  WI_ON_RENDERPATH_START,
  WI_ON_RENDERPATH_STOP,
  WI_ON_RENDERPATH_PREUPDATE,
  WI_ON_FIXEDUPDATE,
  WI_ON_UPDATE,
  WI_ON_RENDERPATH_POSTUPDATE,
  WI_ON_RENDER,
  WI_ON_COMPOSE,

  _WI_ON_COUNT,
} WI_ON;



#ifdef __cplusplus
} // extern "C"
#include "./wi.hpp"
extern "C" {
#endif



/// wrappers:


typedef unsigned int WiEntity;
typedef struct WiComponent {
  int foo;
#ifdef __cplusplus
  void Serialize(wi::Archive& archive, wi::ecs::EntitySerializer& seri);
#endif
} WiComponent;
typedef void* WiComponentManager;
typedef void (*WiComponentFunc)(WiComponent it);
typedef void (*WiEntityFunc)(WiEntity it);
WiEntity WiEntity_create();



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



bool wi_input_down(WI_BUTTON button, int playerIndex);
bool wi_input_hold(WI_BUTTON button, uint32_t frames, bool continuous, int playerIndex);
WI_BUTTON wi_input_whatIsPressed(int playerIndex);
WI_XMFLOAT4 wi_input_getAnalog(WI_GAMEPAD_ANALOG analog, int playerIndex);
bool wi_input_isGamepadButton(WI_BUTTON button);
WiMouseState* wi_input_getMouseState();
bool wi_input_press(WI_BUTTON button, int playerIndex);
WI_XMFLOAT4 wi_input_getPointer();
void wi_input_update(SDL_Window* window, WiCanvas* canvas);
void wi_input_sdlInput_processEvent(SDL_Event* evt);
void wi_input_sdlInput_getKeyboadState(WiKeyboardState* state);
void wi_input_sdlInput_getMouseState(WiMouseState* state);
void wi_input_sdlInput_getControllerState(WiControllerState* state, int index);
void wi_input_sdlInput_setControllerFeedback(WiControllerFeedback* data, int index);
int wi_input_sdlInput_getMaxControllerCount();
void wi_input_sdlInput_update();



void wi_renderer_setShaderPath(char* path);
void wi_renderer_setShaderSourcePath(char* path);
typedef void* WiRenderPath2D;
typedef void* WiRenderPath3D;
typedef void (*WiRenderPathHandler0)(WiRenderPath3D self);
typedef void (*WiRenderPathHandler1)(WiRenderPath3D self, float);
WiRenderPath3D WiRenderPath3D_new();
void WiRenderPath3D_dispose(WiRenderPath3D self);
void WiRenderPath3D_load(WiRenderPath3D self);
void WiRenderPath3D_init(WiRenderPath3D self, SDL_Window* canvas);



void WiRect_fromViewport(WiRect* rect, WiViewport* viewport);



typedef void* WiApplication;
typedef void (*WiApplicationHandler0)(void);
typedef void (*WiApplicationHandler1)(float);
WiApplication WiApplication_new();
void WiApplication_dispose(WiApplication self);
void WiApplication_on(WiApplication self, WI_ON on, void* handler);
void WiApplication_setInfoDisplay(WiApplication self, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                  bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                  bool colorGradingHelper, WiRect* rect);
void WiApplication_setWindow(WiApplication self, SDL_Window* window);
void WiApplication_initialize(WiApplication self);
void WiApplication_activatePath(WiApplication self, WiRenderPath3D renderPath, float fadeSeconds);
void WiApplication_setFullScreen(WiApplication self, bool fullscreen);
void WiApplication_run(WiApplication self);
bool WiApplication_get_isWindowActive(WiApplication self);
void WiApplication_set_isWindowActive(WiApplication self, bool set);
WiCanvas* WiApplication_get_canvas(WiApplication self);
SDL_Window* WiApplication_get_window(WiApplication self);



typedef void (*WiJobHandler)(WiJobArgs* args);
WiJobContext WiJobContext_create();
void wi_jobsystem_dispatch(WiJobContext* ctx, uint32_t jobCount, uint32_t groupSize, WiJobHandler handler);
void wi_jobsystem_execute(WiJobContext* ctx, WiJobHandler handler);
void wi_jobsystem_wait(WiJobContext* ctx);
bool wi_jobsystem_isBusy(WiJobContext* ctx);
uint32_t wi_jobsystem_getThreadCount(WiJobPriority priority);





///
#ifdef __cplusplus
} // extern "C"
#endif
