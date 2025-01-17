#include "../../pch/wi_pch.h"


class Render : public wi::RenderPath3D {
public:
  bool ran;
  void Update(float dt) override;
};


class App : public wi::Application {
  class Render render;

public:
  void Initialize() override;
};


void App::Initialize() {
  wi::Application::Initialize();
  render.init(canvas);
  render.Load();
  ActivatePath(&render);
}

void Render::Update(float dt) {
  wi::RenderPath3D::Update(dt);
  if (!ran) {
    ran = true;
    wi::lua::RunFile("../../.wi/Content/scripts/character_controller/character_controller.lua");
  }
}


App app;


int main(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 600,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  app.SetWindow(sdl_win.get());
  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");
  app.Initialize();
  wi::initializer::WaitForInitializationsToFinish();

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
