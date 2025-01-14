#include "../pch/wi_pch.h"
#include "wiApplication.h"

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

void wi_renderer_setShaderPath(char* path) {
  wi::renderer::SetShaderPath(std::string(path));
}

void wi_renderer_setShaderSourcePath(char* path) {
  wi::renderer::SetShaderSourcePath(std::string(path));
}

WiApplication wi_application_new() {
  return (WiApplication)(new wi::Application());
}

void wi_application_dispose(WiApplication app) {
  delete ((wi::Application*)(app));
}











void wi_tmp_main(SDL_Window* win, int argc, char** argv) {
  wi::Application app {};
  wi::arguments::Parse(argc, argv);
#ifdef WickedEngine_SHADER_DIR
  wi::renderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
#endif

  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  app.infoDisplay.active = true;
  app.infoDisplay.colorspace = true;
  app.infoDisplay.device_name = true;
  app.infoDisplay.fpsinfo = true;
  app.infoDisplay.heap_allocation_counter = false;
  app.infoDisplay.logical_size = false;
  app.infoDisplay.pipeline_count = true;
  app.infoDisplay.pipeline_creation = true;
  app.infoDisplay.resolution = true;
  app.infoDisplay.vram_usage = true;
  app.infoDisplay.watermark = true;

  app.SetWindow(win);
  app.Initialize();
  wi::initializer::WaitForInitializationsToFinish();

  auto game = wi::RenderPath3D {};
  app.ActivatePath(&game);
  SDL_SetWindowTitle(win, wi::version::GetVersionString());
  app.SetFullScreen(true);
}
