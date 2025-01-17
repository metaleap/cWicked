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
  auto me = (WiWrapApplication*)(self);
  me->handlers[on] = handler;
}

void WiApplication_dispose(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  delete me;
}

void WiApplication_setInfoDisplay(WiApplication self, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                  bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                  bool colorGradingHelper, WiRect* rect) {
  auto me = (WiWrapApplication*)(self);
  wi::Application::InfoDisplayer* info = &me->infoDisplay;
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
  auto me = (WiWrapApplication*)(self);
  return me->SetWindow(window);
}

void WiApplication_initialize(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->Initialize();
}

void WiApplication_activatePath(WiApplication self, WiRenderPath3D renderPath, float fadeSeconds) {
  auto me = (WiWrapApplication*)(self);
  auto it = (WiWrapRenderPath3D*)(renderPath);
  return me->ActivatePath(it, fadeSeconds);
}

void WiApplication_setFullScreen(WiApplication self, bool fullscreen) {
  auto me = (WiWrapApplication*)(self);
  return me->SetFullScreen(fullscreen);
}

void WiApplication_setFrameSkip(WiApplication self, bool enabled) {
  auto me = (WiWrapApplication*)(self);
  return me->setFrameSkip(enabled);
}

void WiApplication_setFrameRateLock(WiApplication self, bool enabled) {
  auto me = (WiWrapApplication*)(self);
  return me->setFrameRateLock(enabled);
}

void WiApplication_run(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->Run();
}

bool WiApplication_get_isWindowActive(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->is_window_active;
}

void WiApplication_set_isWindowActive(WiApplication self, bool set) {
  auto me = (WiWrapApplication*)(self);
  me->is_window_active = set;
}

WiCanvas* WiApplication_get_canvas(WiApplication self) {
  static_assert(sizeof(WiCanvas) == sizeof(wi::Canvas));
  auto me = ((WiWrapApplication*)(self));
  return (WiCanvas*)(&me->canvas);
}

SDL_Window* WiApplication_get_window(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->window;
}

float WiApplication_getTargetFrameRate(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->getTargetFrameRate();
}

bool WiApplication_isFaded(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return me->IsFaded();
}

WiWrapRenderPath3D* WiApplication_getActivePath(WiApplication self) {
  auto me = (WiWrapApplication*)(self);
  return (WiWrapRenderPath3D*)(me->GetActivePath());
}
