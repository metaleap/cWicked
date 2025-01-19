#include "../../pch/wi_min_pch.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiApplication.h"
#include ".wi/WickedEngine/wiECS.h"
#include ".wi/WickedEngine/wiImage.h"
#include ".wi/WickedEngine/wiInput.h"
#include ".wi/WickedEngine/wiLua.h"
#include ".wi/WickedEngine/wiRenderer.h"
#include ".wi/WickedEngine/wiScene.h"
#include ".wi/WickedEngine/wiScene_Components.h"
#include ".wi/WickedEngine/wiSprite.h"


#define WI_CONTENT_DIR "../../.wi/Content/"
#define WI_TESTS_DIR   "../../.wi/Samples/Tests/"



class Rend : public wi::RenderPath3D {
  wi::ecs::Entity teapot;
  wi::Sprite      sprite;
public:
  void Load() override;
  void FixedUpdate() override;
};

class App : public wi::Application {
  Rend rend;
public:
  void Initialize() override;
};



void App::Initialize() {
  infoDisplay.active                  = true;
  infoDisplay.colorspace              = true;
  infoDisplay.device_name             = true;
  infoDisplay.fpsinfo                 = true;
  infoDisplay.heap_allocation_counter = false;
  infoDisplay.logical_size            = false;
  infoDisplay.pipeline_count          = true;
  infoDisplay.pipeline_creation       = true;
  infoDisplay.resolution              = true;
  infoDisplay.vram_usage              = true;
  infoDisplay.watermark               = true;
  wi::Application::Initialize();
  rend.init(window);
  rend.Load();
  ActivatePath(&rend, 0.321f);
}



void Rend::Load() {
  wi::renderer::SetTemporalAAEnabled(true);
  wi::renderer::SetToDrawGridHelper(true);
  teapot = wi::scene::LoadModel(WI_CONTENT_DIR "models/teapot.wiscene");
  wi::scene::LoadModel(WI_CONTENT_DIR "models/cameras.wiscene");



  sprite        = wi::Sprite(WI_CONTENT_DIR "logo_small.png");
  sprite.params = wi::image::Params(100, 100, 128, 128);
  AddSprite(&sprite);
  wi::RenderPath3D::Load();
}



void Rend::FixedUpdate() {
  wi::RenderPath3D::FixedUpdate();
}








App  app;
Rend rend;


int main(int argc, char* argv[]) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("WickedEngine simple demos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  auto hwnd = sdl_win.get();
  app.SetWindow(hwnd);
  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");

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
