#include "./wi.hpp"



void WiWrapApplication::FixedUpdate() {
  wi::Application::FixedUpdate();
  auto handler = (WiApplicationHandler0)this->handlers[WI_ON_FIXEDUPDATE];
  if (handler != nullptr)
    handler();
}

void WiWrapApplication::Update(float delta) {
  wi::Application::FixedUpdate();
  auto handler = (WiApplicationHandler1)this->handlers[WI_ON_UPDATE];
  if (handler != nullptr)
    handler(delta);
}

void WiWrapApplication::Initialize() {
  wi::Application::Initialize();
  auto handler = (WiApplicationHandler0)this->handlers[WI_ON_APP_INITIALIZE];
  if (handler != nullptr)
    handler();
}

void WiWrapApplication::Render() {
  wi::Application::Render();
  auto handler = (WiApplicationHandler0)this->handlers[WI_ON_RENDER];
  if (handler != nullptr)
    handler();
}

void WiWrapApplication::Compose(wi::graphics::CommandList cmdList) {
  wi::Application::Compose(cmdList);
  auto handler = (WiApplicationHandler0)this->handlers[WI_ON_COMPOSE];
  if (handler != nullptr)
    handler();
}



WiApplication WiApplication_new() {
  auto ret = new WiWrapApplication();
  for (int i = 0; i < _WI_ON_COUNT; i++)
    ret->handlers[i] = nullptr;
  return (WiApplication)(ret);
}

void WiApplication_on(WiApplication self, WI_ON on, void* handler) {
  auto it = (WiWrapApplication*)(self);
  it->handlers[on] = handler;
}

void WiApplication_dispose(WiApplication self) {
  delete ((WiWrapApplication*)(self));
}

void WiApplication_setInfoDisplay(WiApplication self, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                  bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                  bool colorGradingHelper, WiRect* rect) {
  wi::Application::InfoDisplayer* info = &((WiWrapApplication*)(self))->infoDisplay;
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

void WiApplication_setWindow(WiApplication self, SDL_Window* window) {
  return ((WiWrapApplication*)(self))->SetWindow(window);
}

void WiApplication_initialize(WiApplication self) {
  return ((WiWrapApplication*)(self))->Initialize();
}

void WiApplication_activatePath(WiApplication self, WiRenderPath3D renderPath, float fadeSeconds) {
  return ((WiWrapApplication*)(self))->ActivatePath((WiWrapRenderPath3D*)(renderPath), fadeSeconds);
}

void WiApplication_setFullScreen(WiApplication self, bool fullscreen) {
  return ((WiWrapApplication*)(self))->SetFullScreen(fullscreen);
}

void WiApplication_setFrameSkip(WiApplication self, bool enabled) {
  return ((WiWrapApplication*)(self))->setFrameSkip(enabled);
}

void WiApplication_setFrameRateLock(WiApplication self, bool enabled) {
  return ((WiWrapApplication*)(self))->setFrameRateLock(enabled);
}

void WiApplication_run(WiApplication self) {
  return ((WiWrapApplication*)(self))->Run();
}

bool WiApplication_get_isWindowActive(WiApplication self) {
  return ((WiWrapApplication*)(self))->is_window_active;
}

void WiApplication_set_isWindowActive(WiApplication self, bool set) {
  ((WiWrapApplication*)(self))->is_window_active = set;
}

float WiApplication_getTargetFrameRate(WiApplication self) {
  return ((WiWrapApplication*)(self))->getTargetFrameRate();
}

bool WiApplication_isFaded(WiApplication self) {
  return ((WiWrapApplication*)(self))->IsFaded();
}

WiWrapRenderPath3D* WiApplication_(WiApplication self) {
  return (WiWrapRenderPath3D*)(((WiWrapApplication*)(self))->GetActivePath());
}
