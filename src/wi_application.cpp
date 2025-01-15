#include "./wi.hpp"
#include ".wi/WickedEngine/wiApplication.h"
#include "src/cwicked.h"
#include <cstddef>
#include <cstring>



void WiWrapApplication::FixedUpdate() {
  wi::Application::FixedUpdate();
  auto override = (WiApplicationOn0)this->overrides[WI_ON_FIXEDUPDATE];
  if (override != nullptr)
    override();
}

void WiWrapApplication::Update(float delta) {
  wi::Application::FixedUpdate();
  auto override = (WiApplicationOn1)this->overrides[WI_ON_UPDATE];
  if (override != nullptr)
    override(delta);
}



WiApplication WiApplication_new() {
  auto ret = new WiWrapApplication();
  for (int i = 0; i < _WI_ON_COUNT; i++)
    ret->overrides[i] = nullptr;
  return (WiApplication)(ret);
}

void WiApplication_on(WiApplication app, WI_ON on, void* override) {
  auto it = (WiWrapApplication*)(app);
  it->overrides[on] = override;
}

void WiApplication_dispose(WiApplication app) {
  delete ((WiWrapApplication*)(app));
}

void WiApplication_setInfoDisplay(WiApplication app, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                  bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                  bool colorGradingHelper, WiRect* rect) {
  wi::Application::InfoDisplayer* info = &((WiWrapApplication*)(app))->infoDisplay;
  info->active = active;
  info->watermark = watermark;
  info->fpsinfo = fpsInfo;
  info->device_name = deviceName;
  info->resolution = resolution;
  info->logical_size = logicalSize;
  info->colorspace = colorSpace;
  info->heap_allocation_counter = heapAllocCounter;
  info->pipeline_count = pipelineCount;
  info->pipeline_creation = pipelineCreation;
  info->vram_usage = vramUsage;
  info->size = textSize;
  info->colorgrading_helper = colorGradingHelper;
  if (rect != nullptr)
    info->rect = *((wi::graphics::Rect*)(rect));
}

void WiApplication_setWindow(WiApplication app, SDL_Window* window) {
  return ((WiWrapApplication*)(app))->SetWindow(window);
}

void WiApplication_initialize(WiApplication app) {
  return ((WiWrapApplication*)(app))->Initialize();
}

void WiApplication_activatePath(WiApplication app, WiRenderPath3D renderPath, float fadeSeconds) {
  return ((WiWrapApplication*)(app))->ActivatePath((WiWrapRenderPath3D*)(renderPath), fadeSeconds);
}

void WiApplication_setFullScreen(WiApplication app, bool fullscreen) {
  return ((WiWrapApplication*)(app))->SetFullScreen(fullscreen);
}

void WiApplication_run(WiApplication app) {
  return ((WiWrapApplication*)(app))->Run();
}

bool WiApplication_get_isWindowActive(WiApplication app) {
  return ((WiWrapApplication*)(app))->is_window_active;
}

void WiApplication_set_isWindowActive(WiApplication app, bool set) {
  ((WiWrapApplication*)(app))->is_window_active = set;
}
