#include "../../pch/wi_min_pch.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiEnums.h"
#include ".wi/WickedEngine/wiScene.h"
#include ".wi/WickedEngine/wiScene_Components.h"
#include ".wi/WickedEngine/wiUnorderedMap.h"
#include ".wi/WickedEngine/wiVector.h"
#include <cstddef>
#include <utility>


/* postponed:
    - footprints
    - conversation
*/


#define CC_DIR_PATH "../../.wi/Content/scripts/character_controller/"



class Rend : public wi::RenderPath3D {
  bool                           debugDraws     = false;
  float                          slopeThreshold = 0.2f;   // How much slopeiness will cause character to slide down instead of standing on it
  float                          gravity        = -30.0f;
  bool                           dynamicVoxelization = false;   // Set to true to revoxelize navigation every frame
  wi::scene::CharacterComponent* player              = nullptr;
  wi::vector<wi::scene::CharacterComponent> npcs;
  bool                                      footprintsEnabled = false;
  wi::vector<wi::primitive::Capsule>        characterCapsules;
  wi::VoxelGrid                             voxelGrid;
public:
  void Load() override;
  void Update(float dt) override;
};

class App : public wi::Application {
  Rend rend;
public:
  void Initialize() override;
};


enum Layers : uint32_t {
  Player = 1 << 0,   // 1
  Npc    = 1 << 1,   // 2
};





App  app;
Rend rend;


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
  wi::RenderPath3D::Load();
  voxelGrid.init(128, 32, 128);
  voxelGrid.set_voxelsize(0.25f);
  voxelGrid.center = XMFLOAT3(0, 0.1f, 0);

  setLightShaftsEnabled(false);
  setLightShaftsStrength(0.01f);
  setAO(AO_MSAO);
  setAOPower(0.25f);
  setOutlineEnabled(false);
  setOutlineThreshold(0.11f);
  setOutlineThickness(1.7f);
  setOutlineColor(XMFLOAT4(0, 0, 0, 0.6f));
  setBloomEnabled(true);
  setBloomThreshold(5);
  wi::renderer::SetToDrawDebugEnvProbes(false);
  wi::renderer::SetToDrawGridHelper(false);
  wi::renderer::SetToDrawDebugCameras(false);

  auto anim_scene = wi::scene::Scene();
  wi::scene::LoadModel(anim_scene, CC_DIR_PATH "assets/animations.wiscene");
  wi::scene::LoadModel(CC_DIR_PATH "assets/level.wiscene");

  if (scene->voxel_grids.GetCount() > 0)
    voxelGrid = scene->voxel_grids[0];
  else   // generate a voxel grid in code, player and NPCs not included
    scene->VoxelizeScene(voxelGrid, false, wi::enums::FILTER_NAVIGATION_MESH | wi::enums::FILTER_COLLIDER, ~(Layers::Player | Layers::Npc));

  wi::unordered_map<std::string, std::shared_ptr<wi::scene::Scene>> characters;
  // Create characters from scene metadata components:
  for (size_t i = 0; i < scene->metadatas.GetCount(); i++) {
    auto metadata  = scene->metadatas[i];
    auto entity    = scene->metadatas.GetEntity(i);
    auto transform = scene->transforms.GetComponent(entity);
    if (transform != nullptr) {
      // Determine name of the placed character:
      std::string name = "character";
      if (metadata.string_values.has("name"))
        name = metadata.string_values.get("name");

      // Load character model if doesn't exist yet:
      if (!characters.contains(name)) {
        std::shared_ptr<wi::scene::Scene> tmp = std::make_shared<wi::scene::Scene>();
        wi::scene::LoadModel(*tmp, CC_DIR_PATH "assets/" + name + ".wiscene");
        characters.insert({name, tmp});
      }
    }
  }
}





void Rend::Update(float delta) {
  wi::RenderPath3D::Update(delta);
}





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
