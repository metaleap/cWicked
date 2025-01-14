#include "../pch/wi_pch.h"

#include "cWicked.h"



class WiApp : public wi::Application {
public:
  WiApplicationOnFixedUpdate onFixedUpdate;
  WiApplicationOnUpdate onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};

void WiApp::FixedUpdate() {
  wi::Application::FixedUpdate();
  if (this->onFixedUpdate != nullptr)
    this->onFixedUpdate();
}

void WiApp::Update(float delta) {
  wi::Application::Update(delta);
  if (this->onUpdate != nullptr)
    this->onUpdate(delta);
}



WiApplication wi_Application_new(WiApplicationOnFixedUpdate onFixedUpdate, WiApplicationOnUpdate onUpdate) {
  auto ret = new WiApp();
  ret->onFixedUpdate = onFixedUpdate;
  ret->onUpdate = onUpdate;
  return (WiApplication)(ret);
}

void wi_Application_dispose(WiApplication app) {
  delete ((WiApp*)(app));
}

void wi_Application_setInfoDisplay(WiApplication app, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                   bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                   bool colorGradingHelper, WiRect* rect) {
  wi::Application::InfoDisplayer* info = &((WiApp*)(app))->infoDisplay;
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
  ((WiApp*)(app))->SetWindow(window);
}

void wi_Application_initialize(WiApplication app) {
  ((WiApp*)(app))->Initialize();
}
