#include "../../pch/wi_min_pch.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiECS.h"
#include ".wi/WickedEngine/wiInput.h"
#include ".wi/WickedEngine/wiRenderer.h"
#include ".wi/WickedEngine/wiScene.h"
#include ".wi/WickedEngine/wiScene_Components.h"


#define WI_CONTENT_DIR "../../.wi/Content/"
#define WI_TESTS_DIR   "../../.wi/Samples/Tests/"


enum TestType : uint64_t {
  HELLOWORLD,
  MODEL,
  EMITTEDPARTICLE1,
  EMITTEDPARTICLE2,
  HAIRPARTICLE,
  WATERTEST,
  SHADOWSTEST,
  PHYSICSTEST,
  CLOTHPHYSICSTEST,
  VOLUMETRICTEST,
  INVERSEKINEMATICSTEST,
  INSTANCESTEST,
};



class Rend : public wi::RenderPath3D {
  wi::gui::Label    guiLblTitle;
  wi::gui::ComboBox guiDdnTests;
  wi::ecs::Entity   ikEntity = wi::ecs::INVALID_ENTITY;
public:
  void Load() override;
  void Update(float dt) override;
};



void Rend::Load() {
  this->scaling = 2;

  setSSREnabled(false);
  setReflectionsEnabled(true);
  setFXAAEnabled(false);

  static wi::audio::Sound         sound;
  static wi::audio::SoundInstance soundInstance;
  static wi::gui::Button          guiBtnAudioTest;
  static wi::gui::Slider          guiSldAudioVolume;
  static wi::gui::Slider          guiSldAudioDirection;

  // GUI: title label
  wi::gui::GUI& gui = GetGUI();
  gui.AddWidget(&guiLblTitle);
  guiLblTitle.Create("guiLblTitle");
  guiLblTitle.SetText("WickedEngine Tests");
  guiLblTitle.font.params.h_align = wi::font::WIFALIGN_CENTER;
  guiLblTitle.SetSize(XMFLOAT2(240, 22));
  guiLblTitle.SetPos(XMFLOAT2(789, 0));

  // GUI: audio play/stop button
  guiBtnAudioTest.Create("guiBtnAudioTest");
  gui.AddWidget(&guiBtnAudioTest);
  guiBtnAudioTest.SetText("Play Audio");
  guiBtnAudioTest.SetSize(XMFLOAT2(240, 20));
  guiBtnAudioTest.SetPos(XMFLOAT2(789, 20));
  guiBtnAudioTest.OnClick([&](wi::gui::EventArgs _) {
    static bool playing = false;
    if (!sound.IsValid()) {
      if (!wi::audio::CreateSound(WI_CONTENT_DIR "models/water.wav", &sound))
        abort();
      soundInstance.SetLooped(true);
      if (!wi::audio::CreateSoundInstance(&sound, &soundInstance))
        abort();
      wi::audio::SetVolume(guiSldAudioVolume.GetValue() / 100.0f, &soundInstance);
    }
    if (playing) {
      wi::audio::Stop(&soundInstance);
      guiBtnAudioTest.SetText("Play Audio");
    } else {
      wi::audio::Play(&soundInstance);
      guiBtnAudioTest.SetText("Stop Audio");
    }
    playing = !playing;
  });

  // GUI: audio volume slider
  guiSldAudioVolume.Create(0, 100, 50, 20, "guiSldAudioVolume");
  gui.AddWidget(&guiSldAudioVolume);
  guiSldAudioVolume.SetText("Volume");
  guiSldAudioVolume.SetSize(XMFLOAT2(240, 20));
  guiSldAudioVolume.SetPos(XMFLOAT2(789, 40));
  guiSldAudioVolume.OnSlide([&](wi::gui::EventArgs evt) { wi::audio::SetVolume(evt.fValue / 100.0f, &soundInstance); });

  // GUI: audio direction slider
  guiSldAudioDirection.Create(-1, 1, 0, 10000, "guiSldAudioDirection");
  gui.AddWidget(&guiSldAudioDirection);
  guiSldAudioDirection.SetText("Direction");
  guiSldAudioDirection.SetSize(XMFLOAT2(240, 20));
  guiSldAudioDirection.SetPos(XMFLOAT2(789, 60));
  guiSldAudioDirection.OnSlide([&](wi::gui::EventArgs evt) {
    wi::audio::SoundInstance3D au3d;
    au3d.emitterPos  = XMFLOAT3(evt.fValue, 0, 0);
    au3d.listenerPos = XMFLOAT3(0, 0, -1);
    wi::audio::Update3D(&soundInstance, au3d);
  });

  // GUI: test selection drop-down menu
  guiDdnTests.Create("guiDdnTests");
  gui.AddWidget(&guiDdnTests);
  guiDdnTests.SetText("Demo:");
  guiDdnTests.SetSize(XMFLOAT2(240, 20));
  guiDdnTests.SetPos(XMFLOAT2(789, 80));
  guiDdnTests.AddItem("HelloWorld", TestType::HELLOWORLD);
  guiDdnTests.AddItem("Model", TestType::MODEL);
  guiDdnTests.AddItem("EmittedParticle1", TestType::EMITTEDPARTICLE1);
  guiDdnTests.AddItem("EmittedParticle2", TestType::EMITTEDPARTICLE2);
  guiDdnTests.AddItem("HairParticle", HAIRPARTICLE);
  guiDdnTests.AddItem("Water Test", WATERTEST);
  guiDdnTests.AddItem("Shadows Test", SHADOWSTEST);
  guiDdnTests.AddItem("Physics Test", PHYSICSTEST);
  guiDdnTests.AddItem("Cloth Physics Test", CLOTHPHYSICSTEST);
  guiDdnTests.AddItem("Volumetric Test", VOLUMETRICTEST);
  guiDdnTests.AddItem("Inverse Kinematics", INVERSEKINEMATICSTEST);
  guiDdnTests.AddItem("65k Instances", INSTANCESTEST);
  guiDdnTests.SetMaxVisibleItemCount(11);
  guiDdnTests.SetSelected(-1);
  guiDdnTests.OnSelect([&](wi::gui::EventArgs evt) {
    {   // reset whatever previous demo might have modified
      wi::renderer::ClearWorld(wi::scene::GetScene());
      this->ClearSprites();
      wi::renderer::SetTemporalAAEnabled(false);
      wi::renderer::SetToDrawGridHelper(false);
      wi::eventhandler::SetVSync(true);
      wi::profiler::SetEnabled(false);
      wi::scene::GetScene().weather = wi::scene::WeatherComponent();
      this->ClearFonts();
      if (wi::lua::GetLuaState() != nullptr)
        wi::lua::KillProcesses();
      ikEntity = wi::ecs::INVALID_ENTITY;
    }

    {   // reset cam pos
      wi::scene::TransformComponent transform;
      transform.Translate(XMFLOAT3(0, 2, -4.5));
      transform.UpdateTransform();
      wi::scene::GetCamera().TransformCamera(transform);
    }

    switch (evt.userdata) {
      case TestType::HELLOWORLD:
        static wi::Sprite sprite;
        sprite                           = wi::Sprite(WI_TESTS_DIR "images/movingtex.png", WI_TESTS_DIR "images/HelloWorld.png");
        sprite.params.pos                = XMFLOAT3(GetLogicalWidth() / 2, GetLogicalHeight() / 2, 0);
        sprite.params.siz                = XMFLOAT2(987, 789);
        sprite.params.pivot              = XMFLOAT2(0.5, 0.5);
        sprite.anim.rot                  = XM_PI * 0.25;
        sprite.anim.wobbleAnim.amount    = XMFLOAT2(0.16f, 0.16f);
        sprite.anim.movingTexAnim.speedX = 0;
        sprite.anim.movingTexAnim.speedY = 3.21f;
        this->AddSprite(&sprite);
        break;

      case TestType::MODEL:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/teapot.wiscene");
        break;

      case TestType::EMITTEDPARTICLE1:
        wi::scene::LoadModel(WI_CONTENT_DIR "models/emitter_smoke.wiscene");
        break;

      case TestType::EMITTEDPARTICLE2:
        wi::scene::LoadModel(WI_CONTENT_DIR "models/emitter_skinned.wiscene");
        break;

      case TestType::HAIRPARTICLE:
        wi::scene::LoadModel(WI_CONTENT_DIR "models/hairparticle_torus.wiscene", XMMatrixTranslation(0, 0.77f, 0));
        break;

      case TestType::WATERTEST:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/water_test.wiscene", XMMatrixTranslation(0, 1, 0));
        break;

      case TestType::SHADOWSTEST:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/shadows_test.wiscene", XMMatrixTranslation(0, 1, 0));
        break;

      case TestType::PHYSICSTEST:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/physics_test.wiscene");
        break;

      case TestType::CLOTHPHYSICSTEST:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/cloth_test.wiscene", XMMatrixTranslation(0, 3, 4));
        break;

      case TestType::VOLUMETRICTEST:
        wi::renderer::SetTemporalAAEnabled(true);
        wi::scene::LoadModel(WI_CONTENT_DIR "models/volumetric_test.wiscene", XMMatrixTranslation(0, 0, 4));
        break;

      case TestType::INSTANCESTEST:
        {
          wi::scene::LoadModel(WI_CONTENT_DIR "models/cube.wiscene");
          wi::scene::Scene& scene_global = wi::scene::GetScene();
          scene_global.Entity_CreateLight("light", XMFLOAT3(0, 2, -4), XMFLOAT3(1, 1, 1), 4);
          wi::ecs::Entity cube  = scene_global.Entity_FindByName("Cube");
          const float     scale = 0.06f;
          for (int x = 0; x < 32; x++)
            for (int y = 0; y < 32; y++)
              for (int z = 0; z < 64; z++) {
                wi::ecs::Entity                dupl      = scene_global.Entity_Duplicate(cube);
                wi::scene::TransformComponent* transform = scene_global.transforms.GetComponent(dupl);
                transform->Scale(XMFLOAT3(scale, scale, scale));
                transform->Translate(XMFLOAT3((-5.5f + 11 * float(x) / 32.f), (-0.5f + 5.0f * float(y) / 32.f), (float(z) * 0.5f)));
              }
          scene_global.Entity_Remove(cube);
        }
        break;

      case TestType::INVERSEKINEMATICSTEST:
        {
          wi::scene::Scene scene_ik;
          wi::scene::LoadModel(scene_ik, WI_CONTENT_DIR "scripts/character_controller/assets/character.wiscene", XMMatrixScaling(2, 2, 2),
                               false);
          if (scene_ik.humanoids.GetCount() == 0)
            abort();
          wi::scene::HumanoidComponent humanoid = scene_ik.humanoids[0];
          humanoid.SetLookAtEnabled(false);
          ikEntity = humanoid.bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::LeftHand];
          if (ikEntity != wi::ecs::INVALID_ENTITY) {
            wi::scene::InverseKinematicsComponent& ik = scene_ik.inverse_kinematics.Create(ikEntity);
            ik.chain_length                           = 2;   // lower and upper arm included (two parents in hierarchy of hand)
            ik.iteration_count                        = 5;   // precision of ik sim
            ik.target                                 = wi::ecs::CreateEntity();
            scene_ik.transforms.Create(ik.target);
          }
          wi::scene::GetScene().Merge(scene_ik);
          auto weather     = &wi::scene::GetScene().weather;
          weather->ambient = XMFLOAT3(0.33f, 0.44f, 0.55f);
          weather->horizon = XMFLOAT3(0.38f, 0.38f, 0.38f);
          weather->zenith  = XMFLOAT3(0.42f, 0.42f, 0.42f);
        }
        break;
    }
  });
  wi::RenderPath3D::Load();
}

void Rend::Update(float delta) {
  auto idx = guiDdnTests.GetSelected();
  if (idx >= 0)
    switch (guiDdnTests.GetItemUserData(idx)) {
      case TestType::MODEL:
        {
          wi::scene::Scene& scene_global = wi::scene::GetScene();
          wi::ecs::Entity   teapot_base  = scene_global.Entity_FindByName("Base");
          assert(teapot_base != wi::ecs::INVALID_ENTITY);
          wi::scene::TransformComponent* transform = scene->transforms.GetComponent(teapot_base);
          assert(transform != nullptr);
          float rotation = delta;
          transform->Rotate(XMVectorSet(0, rotation, 0, 1));
        }
        break;
      case TestType::INSTANCESTEST:
        {
          static wi::Timer       timer;
          float                  sec = (float) (timer.elapsed_seconds());
          wi::jobsystem::context ctx;
          scene->materials[0].SetEmissiveColor(XMFLOAT4(1, 1, 1, 1));
          wi::jobsystem::Dispatch(ctx, (uint32_t) scene->transforms.GetCount(), 1024, [&](wi::jobsystem::JobArgs job) {
            wi::scene::TransformComponent& transform = scene->transforms[job.jobIndex];
            float                          y = std::sin(sec + 20.0f * (float) job.jobIndex / (float) scene->transforms.GetCount()) * 0.1f;
            XMStoreFloat4x4(&transform.world, transform.GetLocalMatrix() * XMMatrixTranslation(0, y, 0));
          });
          wi::jobsystem::Dispatch(ctx, (uint32_t) scene->objects.GetCount(), 1024, [&](wi::jobsystem::JobArgs job) {
            wi::scene::ObjectComponent& object = scene->objects[job.jobIndex];
            float f = std::pow(std::sin(-sec * 2.0f + 4.0f * (float) job.jobIndex / (float) scene->objects.GetCount()) * 0.5f + 0.5f, 32.0f);
            object.emissiveColor = XMFLOAT4(0, 0.25f, 1.0f, f * 3.0f);
          });
          wi::jobsystem::Wait(ctx);
        }
        break;
      case TestType::INVERSEKINEMATICSTEST:
        if (ikEntity != wi::ecs::INVALID_ENTITY) {
          const wi::input::MouseState& mouse = wi::input::GetMouseState();
          wi::primitive::Ray           ray   = wi::renderer::GetPickRay(mouse.position.x, mouse.position.y, *this);
          XMVECTOR                     plane = XMVectorSet(0, 0, 1, 0.2f);
          XMVECTOR                     intersect
              = XMPlaneIntersectLine(plane, XMLoadFloat3(&ray.origin), XMLoadFloat3(&ray.origin) + XMLoadFloat3(&ray.direction) * 10000.0f);
          wi::scene::Scene&              scene_global = wi::scene::GetScene();
          wi::scene::TransformComponent* target
              = scene_global.transforms.GetComponent((scene_global.inverse_kinematics.GetComponent(ikEntity))->target);
          target->ClearTransform();
          XMFLOAT3 intersect_;
          XMStoreFloat3(&intersect_, intersect);
          target->Translate(intersect_);
          target->UpdateTransform();
          {   // draw debug ik target position:
            wi::renderer::RenderablePoint pp;
            pp.position = target->GetPosition();
            pp.color    = XMFLOAT4(0, 1, 1, 1);
            pp.size     = 0.321f;
            wi::renderer::DrawPoint(pp);
            pp.position = scene_global.transforms.GetComponent(ikEntity)->GetPosition();
            pp.color    = XMFLOAT4(1, 0, 0, 1);
            pp.size     = 0.123f;
            wi::renderer::DrawPoint(pp);
          }
        }
        break;
    }
  wi::RenderPath3D::Update(delta);
}








wi::Application app;
Rend            rend;


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

  app.infoDisplay.active                  = true;
  app.infoDisplay.colorspace              = true;
  app.infoDisplay.device_name             = true;
  app.infoDisplay.fpsinfo                 = true;
  app.infoDisplay.heap_allocation_counter = false;
  app.infoDisplay.logical_size            = false;
  app.infoDisplay.pipeline_count          = true;
  app.infoDisplay.pipeline_creation       = true;
  app.infoDisplay.resolution              = true;
  app.infoDisplay.vram_usage              = true;
  app.infoDisplay.watermark               = true;
  app.Initialize();
  rend.init(hwnd);
  rend.Load();
  app.ActivatePath(&rend, 0.321f);

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
