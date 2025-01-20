#include "../../pch/wi_min_pch.h"


#define WI_CONTENT_DIR "../../.wi/Content/"
#define WI_TESTS_DIR   "../../.wi/Samples/Tests/"



class Game : public wi::RenderPath3D {
  wi::ecs::Entity             teapot;
  wi::Sprite                  sprite;
  wi::vector<wi::ecs::Entity> camAnimRoute;
  int                         camAnimRot   = 0;
  float                       camAnimTt    = 0.0f;
  float                       camAnimSpeed = 0.4f;
  XMFLOAT2 spriteVelocity = XMFLOAT2((wi::random::GetRandom(1.0f) * 2.0f - 1.0f) * 4.0f, (wi::random::GetRandom(1.0f) * 2.0f - 1.0f) * 4.0f);
public:
  void Load() override;
  void FixedUpdate() override;
  void Update(float dt) override;
};

class App : public wi::Application {
  Game game;
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
  game.init(window);
  game.Load();
  ActivatePath(&game, 0.321f);
}



void Game::Load() {
  wi::renderer::SetToDrawGridHelper(true);
  teapot = wi::scene::LoadModel(WI_CONTENT_DIR "models/teapot.wiscene", XMMatrixIdentity(), true);

  wi::scene::LoadModel(WI_CONTENT_DIR "models/cameras.wiscene");
  for (int i = 0; true; i++) {
    auto cam = scene->Entity_FindByName(std::format("cam{}", i));
    if (cam == wi::ecs::INVALID_ENTITY)
      break;
    camAnimRoute.push_back(cam);
  }

  sprite        = wi::Sprite(WI_CONTENT_DIR "logo_small.png");
  sprite.params = wi::image::Params(100, 100, 128, 128);
  AddSprite(&sprite);
  wi::RenderPath3D::Load();
}



void Game::Update(float delta) {
  wi::RenderPath3D::Update(delta);
  auto a = scene->transforms.GetComponent(camAnimRoute[(camAnimRot - 1) % camAnimRoute.size()]);
  auto b = scene->transforms.GetComponent(camAnimRoute[(camAnimRot + 0) % camAnimRoute.size()]);
  auto c = scene->transforms.GetComponent(camAnimRoute[(camAnimRot + 1) % camAnimRoute.size()]);
  auto d = scene->transforms.GetComponent(camAnimRoute[(camAnimRot + 2) % camAnimRoute.size()]);

  static wi::scene::TransformComponent target;
  target.CatmullRom(*a, *b, *c, *d, camAnimTt);
  target.UpdateTransform();
  camera->TransformCamera(target);
  camera->UpdateCamera();

  camAnimTt += (camAnimSpeed * delta);
  if (camAnimTt >= 1.0f) {
    camAnimTt = 0.0f;
    camAnimRot++;
  }
}



void Game::FixedUpdate() {
  auto pos = sprite.params.pos;
  auto siz = sprite.params.siz;

  if ((pos.x + siz.x) >= GetLogicalWidth())
    spriteVelocity.x *= -1;
  if ((pos.y + siz.y) >= GetLogicalHeight())
    spriteVelocity.y *= -1;
  if (pos.x <= 0)
    spriteVelocity.x *= -1;
  if (pos.y <= 0)
    spriteVelocity.y *= -1;

  pos               = XMFLOAT3(pos.x + spriteVelocity.x, pos.y + spriteVelocity.y, pos.z);
  sprite.params.pos = pos;

  auto teapot_transform = scene->transforms.GetComponent(teapot);
  teapot_transform->RotateRollPitchYaw(XMFLOAT3(0, 0, 0.01f));
  teapot_transform->UpdateTransform();

  wi::RenderPath3D::FixedUpdate();
}






App  app;
Game rend;


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
