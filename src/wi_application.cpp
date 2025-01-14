#include "./wi.hpp"



void WiWrapApplication::FixedUpdate() {
  wi::Application::FixedUpdate();
  if (this->onFixedUpdate != nullptr)
    this->onFixedUpdate();
}

void WiWrapApplication::Update(float delta) {
  wi::Application::Update(delta);
  if (this->onUpdate != nullptr)
    this->onUpdate(delta);
}



WiApplication wi_Application_new(WiApplicationOnFixedUpdate onFixedUpdate, WiApplicationOnUpdate onUpdate) {
  auto ret = new WiWrapApplication();
  ret->onFixedUpdate = onFixedUpdate;
  ret->onUpdate = onUpdate;
  return (WiApplication)(ret);
}

void wi_Application_dispose(WiApplication app) {
  delete ((WiWrapApplication*)(app));
}

void wi_Application_setInfoDisplay(WiApplication app, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
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

void wi_Application_setWindow(WiApplication app, SDL_Window* window) {
  ((WiWrapApplication*)(app))->SetWindow(window);
}

void wi_Application_initialize(WiApplication app) {
  ((WiWrapApplication*)(app))->Initialize();
}

void wi_Application_activatePath(WiApplication app, WiRenderPath3D renderPath, float fadeSeconds) {
  ((WiWrapApplication*)(app))->ActivatePath((WiWrapRenderPath3D*)(renderPath), fadeSeconds);
}

void wi_Application_setFullScreen(WiApplication app, bool fullscreen) {
  ((WiWrapApplication*)(app))->SetFullScreen(fullscreen);
}

void wi_Application_run(WiApplication app) {
  ((WiWrapApplication*)(app))->Run();
}

bool wi_Application_isWindowActive(WiApplication app, bool* set) {
  if (set != nullptr)
    ((WiWrapApplication*)(app))->is_window_active = *set;
  return ((WiWrapApplication*)(app))->is_window_active;
}
