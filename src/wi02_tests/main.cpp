#include "../../pch/wi_min_pch.h"

enum class TestType {
  HELLOWORLD,
  MODEL,
  EMITTEDPARTICLE1,
  EMITTEDPARTICLE2,
  HAIRPARTICLE,
  LUASCRIPT,
  WATERTEST,
  SHADOWSTEST,
  PHYSICSTEST,
  CLOTHPHYSICSTEST,
  JOBSYSTEMTEST,
  FONTTEST,
  VOLUMETRICTEST,
  SPRITETEST,
  LIGHTMAPBAKETEST,
  NETWORKTEST,
  CONTROLLERTEST,
  INVERSEKINEMATICSTEST,
  INSTANCESTEST,
  CONTAINERPERF,
};



class Rend : public wi::RenderPath3D {
  wi::gui::Label    label;
  wi::gui::ComboBox testSelector;
  wi::ecs::Entity   ik_entity = wi::ecs::INVALID_ENTITY;
public:
  void Load() override;
  void Update(float dt) override;
};

class App : public wi::Application {
  class Rend render;
public:
  void Initialize() override;
};

void App::Initialize() {
  wi::Application::Initialize();
  this->infoDisplay.active                  = true;
  this->infoDisplay.colorspace              = true;
  this->infoDisplay.device_name             = true;
  this->infoDisplay.fpsinfo                 = true;
  this->infoDisplay.heap_allocation_counter = false;
  this->infoDisplay.logical_size            = false;
  this->infoDisplay.pipeline_count          = true;
  this->infoDisplay.pipeline_creation       = true;
  this->infoDisplay.resolution              = true;
  this->infoDisplay.vram_usage              = true;
  this->infoDisplay.watermark               = true;
  this->render.init(canvas);
  this->render.Load();
  this->ActivatePath(&this->render, 0.321f);
}

void Rend::Load() {
  wi::RenderPath3D::Load();
}

App app;

int main(int argc, char* argv[]) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("WickedEngine simple demos?!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  app.SetWindow(sdl_win.get());
  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");
  // app.Initialize();
  // wi::initializer::WaitForInitializationsToFinish();

  bool quit = false;
  while (!quit) {
    app.Run();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              quit = true;
              break;
            case SDL_WINDOWEVENT_RESIZED:
              app.SetWindow(app.window);
              break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
              app.is_window_active = false;
              break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
              app.is_window_active = true;
              break;
          }
          break;
      }
      wi::input::sdlinput::ProcessEvent(event);
    }
  }

  SDL_Quit();
  return 0;
}
