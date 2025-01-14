#include "../pch/wi_pch.h"

#include "cWicked.h"



const char* wi_version_getVersionString() {
  return wi::version::GetVersionString();
}

const char* wi_version_getCreditsString() {
  return wi::version::GetCreditsString();
}

int wi_version_getMajor() {
  return wi::version::GetMajor();
}

int wi_version_getMinor() {
  return wi::version::GetMinor();
}

int wi_version_getRevision() {
  return wi::version::GetRevision();
}

void wi_arguments_parse(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);
}

void wi_initializer_waitForInitializationsToFinish() {
  wi::initializer::WaitForInitializationsToFinish();
}

void wi_renderer_setShaderPath(char* path) {
  wi::renderer::SetShaderPath(std::string(path));
}

void wi_renderer_setShaderSourcePath(char* path) {
  wi::renderer::SetShaderSourcePath(std::string(path));
}

WiRect wi_graphics_Rect(int32_t left, int32_t top, int32_t right, int32_t bottom) {
  wi::graphics::Rect ret = wi::graphics::Rect {.left = left, .top = top, .right = right, .bottom = bottom};
  return *((WiRect*)(&ret));
}

WiViewport wi_graphics_Viewport(float top_left_x, float top_left_y, float width, float height, float min_depth, float max_depth) {
  wi::graphics::Viewport ret = wi::graphics::Viewport {
      .top_left_x = top_left_x, .top_left_y = top_left_y, .width = width, .height = height, .min_depth = min_depth, .max_depth = max_depth};
  return *((WiViewport*)(&ret));
}

void wi_graphics_Rect_fromViewport(WiRect* rect, WiViewport* viewport) {
  wi::graphics::Rect* r = (wi::graphics::Rect*)rect;
  wi::graphics::Viewport* vp = (wi::graphics::Viewport*)viewport;
  r->from_viewport(*vp);
}

WiApplication wi_Application_new() {
  return (WiApplication)(new wi::Application());
}

void wi_Application_dispose(WiApplication app) {
  delete ((wi::Application*)(app));
}

void wi_Application_infoDisplay(WiApplication app, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
                                bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize,
                                bool colorGradingHelper, WiRect* rect) {
  wi::Application::InfoDisplayer* info = &((wi::Application*)(app))->infoDisplay;
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
  ((wi::Application*)(app))->SetWindow(window);
}

void wi_Application_initialize(WiApplication app) {
  ((wi::Application*)(app))->Initialize();
}
