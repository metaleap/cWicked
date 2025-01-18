#include "../../pch/wi_min_pch.h"
#include ".wi/WickedEngine/wiAudio.h"
#include ".wi/WickedEngine/wiGUI.h"
#include <cstdlib>


#define WI_CONTENT_DIR "../../.wi/Content/"


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
  wi::gui::Label    guiLblTitle;
  wi::gui::ComboBox testSelector;
  wi::ecs::Entity   ik_entity = wi::ecs::INVALID_ENTITY;
public:
  void Load() override;
  // void Update(float dt) override;
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
  guiSldAudioVolume.SetSize(XMFLOAT2(240, 20));
  guiSldAudioVolume.SetPos(XMFLOAT2(789, 40));
  guiSldAudioVolume.OnSlide([&](wi::gui::EventArgs evt) { wi::audio::SetVolume(evt.fValue / 100.0f, &soundInstance); });



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
  auto sdl_win = sdl2::make_window("WickedEngine simple demos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900,
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
