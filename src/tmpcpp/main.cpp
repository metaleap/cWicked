#include "../../.wi/WickedEngine/WickedEngine.h"



class Game : public wi::RenderPath3D {
public:
  Game() = default;
  ~Game() = default;
  void Load() override;
  void Start() override;
  void Stop() override;
  void PreUpdate() override;
  void FixedUpdate() override;
  void Update(float deltaTime) override;
  void PostUpdate() override;
};

void Game::Load() {
  wi::RenderPath3D::Load();
}

void Game::Start() {
  wi::RenderPath3D::Start();
}

void Game::Stop() {
  wi::RenderPath3D::Stop();
}

void Game::PreUpdate() {
  wi::RenderPath3D::PreUpdate();
}

void Game::FixedUpdate() {
  wi::RenderPath3D::FixedUpdate();
}

void Game::Update(float deltaTime) {
  wi::RenderPath3D::Update(deltaTime);
}

void Game::PostUpdate() {
  wi::RenderPath3D::PostUpdate();
}



char* engineDirPath;


class App : public wi::Application {
public:
  void mainLoop(SDL_Window* sdlWin) {
    bool quit = false;
    bool ran = false;
    SDL_Event sdl_evt;

    while (!quit) {
      SDL_PumpEvents();
      this->Run();

      // if (!ran) {
      //   ran = true;
      //   wi::lua::RunFile("../../.wi/Content/scripts/character_controller/character_controller.lua");
      // }

      while (((bool)(SDL_PollEvent(&sdl_evt))) && !quit)
        switch (sdl_evt.type) {
          case SDL_QUIT:
            quit = true;
            break;
          case SDL_WINDOWEVENT:
            switch (sdl_evt.window.event) {
              case SDL_WINDOWEVENT_CLOSE:
                quit = true;
                break;
              case SDL_WINDOWEVENT_FOCUS_LOST:
                this->is_window_active = false;
                break;
              case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->is_window_active = true;
                break;
              case SDL_WINDOWEVENT_SIZE_CHANGED:
              case SDL_WINDOWEVENT_RESIZED:
                this->SetWindow(sdlWin);
                break;
            }
            break;
          default:
            wi::input::sdlinput::ProcessEvent(sdl_evt);
            break;
        }
    }
  }
};


int main(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);

  if (0 != *sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to init SDL: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  auto sdl_win = sdl2::make_window("Ensuring up-to-date shaders for this PC — please wait a minute...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   960, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if (!sdl_win) {
    fprintf(stderr, "Failed to make window: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  wi::renderer::SetShaderPath("../../.wi/.shaders/");
  wi::renderer::SetShaderSourcePath("../../.wi/WickedEngine/shaders/");

  App* app = new App();
  app->infoDisplay.active = true;
  app->infoDisplay.colorspace = true;
  app->infoDisplay.device_name = true;
  app->infoDisplay.fpsinfo = true;
  app->infoDisplay.heap_allocation_counter = false;
  app->infoDisplay.logical_size = false;
  app->infoDisplay.pipeline_count = true;
  app->infoDisplay.pipeline_creation = true;
  app->infoDisplay.resolution = true;
  app->infoDisplay.vram_usage = true;
  app->infoDisplay.watermark = true;
  app->infoDisplay.colorgrading_helper = false;
  app->infoDisplay.size = 22;


  auto hwnd = sdl_win.get();
  app->SetWindow(hwnd);
  app->Initialize();
  // wi::initializer::WaitForInitializationsToFinish();

  Game game = Game();
  game.init(hwnd);
  game.Load();
  app->ActivatePath(&game);
  // SDL_SetWindowTitle(hwnd, wi::version::GetVersionString());
  // app->SetFullScreen(true);
  app->mainLoop(hwnd);
  SDL_Quit();
}
