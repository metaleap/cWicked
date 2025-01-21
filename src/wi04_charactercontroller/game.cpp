#include "./app.h"



void Game::Load() {
  wi::RenderPath3D::Load();
  wi::input::HidePointer(true);
  this->voxelGrid.init(128, 32, 128);
  this->voxelGrid.set_voxelsize(0.25f);
  this->voxelGrid.center = XMFLOAT3(0, 0.1f, 0);

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
  wi::renderer::SetToDrawDebugEnvProbes(this->debugDraws);
  wi::renderer::SetToDrawGridHelper(this->debugDraws);
  wi::renderer::SetToDrawDebugCameras(this->debugDraws);

  auto anim_scene = wi::scene::Scene();
  wi::scene::LoadModel(anim_scene, CC_DIR_PATH "assets/animations.wiscene");
  wi::scene::LoadModel(CC_DIR_PATH "assets/level.wiscene");

  if (scene->voxel_grids.GetCount() > 0)
    this->voxelGrid = scene->voxel_grids[0];
  else   // generate a voxel grid in code, player and NPCs not included
    scene->VoxelizeScene(this->voxelGrid, false, wi::enums::FILTER_NAVIGATION_MESH | wi::enums::FILTER_COLLIDER,
                         ~(Layers::Player | Layers::Npc));

  wi::unordered_map<std::string, std::shared_ptr<wi::scene::Scene>> character_models;
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
      if (!character_models.contains(name)) {
        std::shared_ptr<wi::scene::Scene> tmp = std::make_shared<wi::scene::Scene>();
        wi::scene::LoadModel(*tmp, CC_DIR_PATH "assets/" + name + ".wiscene");
        character_models.insert({name, tmp});
      }
      if ((this->player == nullptr) && metadata.preset == wi::scene::MetadataComponent::Preset::Player)
        this->player = new Character(character_models[name].get(), transform, true, anim_scene, metadata.string_values.get("animset"));
      else if (metadata.preset == wi::scene::MetadataComponent::Preset::NPC) {
        auto npc = new Character(character_models[name].get(), transform, false, anim_scene, metadata.string_values.get("animset"));
        this->npcs.push_back(npc);
      }
    }
  }

  // local camera = ThirdPersonCamera(player)
}



void Game::Update(float delta) {
  wi::RenderPath3D::Update(delta);
}
