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
    auto& metadata  = scene->metadatas[i];
    auto  entity    = scene->metadatas.GetEntity(i);
    auto  transform = scene->transforms.GetComponent(entity);
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

  this->cam = ThirdPersonCamera(player);
  this->scene->transforms.Create(this->cam.cam_entity);
}



void Game::Update(float delta) {
  if (wi::input::Press(wi::input::BUTTON::KEYBOARD_BUTTON_F5))
    this->debugDraws = !this->debugDraws;

  this->player->update(delta, this->debugDraws, this->characterCapsules);
  for (auto npc : this->npcs)
    npc->update(delta, this->debugDraws, this->characterCapsules);
  this->cam.update(this->debugDraws);

  if (this->dynamicVoxelization) {
    this->voxelGrid.cleardata();
    scene->VoxelizeScene(voxelGrid, false, wi::enums::FILTER::FILTER_NAVIGATION_MESH | wi::enums::FILTER::FILTER_COLLIDER,
                         ~(Layers::Player | Layers::Npc));   // player and npc layers not included in voxelization
  }

  if (this->debugDraws && !wi::backlog::isActive()) {   // Do some debug draw geometry:
    auto target_transform = scene->transforms.GetComponent(this->player->boneNeck);

    // camera target box and axis
    wi::renderer::DrawBox(target_transform->world);

    wi::renderer::DrawPoint(
        wi::renderer::RenderablePoint {.position = target_transform->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {
        .position = scene->transforms.GetComponent(this->player->boneHead)->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {
        .position = scene->transforms.GetComponent(this->player->boneHandLeft)->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {
        .position = scene->transforms.GetComponent(this->player->boneHandRight)->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {
        .position = scene->transforms.GetComponent(this->player->boneFootLeft)->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {
        .position = scene->transforms.GetComponent(this->player->boneFootRight)->GetPosition(), .size = 0.05f, .color = XMFLOAT4(0, 1, 1, 1)});

    auto capsule = scene->colliders.GetComponent(player->model)->capsule;
    wi::renderer::DrawCapsule(capsule);

    wi::renderer::DrawDebugText(this->player->state.c_str(),
                                wi::renderer::DebugTextParams {.position = capsule.base,
                                                               .scaling  = 1,
                                                               .color    = XMFLOAT4(1, 1, 1, 1),
                                                               .flags    = wi::renderer::DebugTextParams::FLAGS::CAMERA_FACING
                                                                        | wi::renderer::DebugTextParams::FLAGS::CAMERA_SCALING});
    wi::renderer::DrawVoxelGrid(&this->voxelGrid);
  }

  wi::RenderPath3D::Update(delta);
}
