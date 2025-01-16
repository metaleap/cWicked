#include "../../.wi/WickedEngine/WickedEngine.h"
#include <cstdio>


#define CONTENT_DIR "../../.wi/Content/"


class Render : public wi::RenderPath3D {
public:
  void Update(float dt) override;
};


class App : public wi::Application {
  class Render render;

public:
  void Initialize() override;
};


void Render::Update(float dt) {
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>A%zu<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", wi::scene::GetScene().characters.GetCount());
  fflush(stdout);
  wi::RenderPath3D::Update(dt);
}


void App::Initialize() {
  sleep(1);
  wi::Application::Initialize();
  sleep(1);
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>B%zu<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", wi::scene::GetScene().characters.GetCount());
  fflush(stdout);
  render.init(canvas);
  sleep(1);
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>C%zu<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", wi::scene::GetScene().characters.GetCount());
  fflush(stdout);
  render.Load();
  sleep(1);
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>D%zu<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", wi::scene::GetScene().characters.GetCount());
  fflush(stdout);
  ActivatePath(&render);
  sleep(1);
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>E%zu<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", wi::scene::GetScene().characters.GetCount());
  fflush(stdout);
}


App app;


int main(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("Ensuring up-to-date shaders for this PC: please wait a minute....", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   960, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  app.SetWindow(sdl_win.get());
  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");

  bool quit = false;
  while (!quit) {
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
    app.Run();
  }

  SDL_Quit();
  return 0;
}
