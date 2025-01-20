#pragma once

#include "../../pch/wi_min_pch.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiECS.h"
#include ".wi/WickedEngine/wiMath.h"


#define CC_DIR_PATH "../../.wi/Content/scripts/character_controller/"



enum Layers : uint32_t {
  Player = 1 << 0,   // 1
  Npc    = 1 << 1,   // 2
};


class Character {
public:
  Character(wi::scene::Scene*, wi::scene::TransformComponent*, bool, wi::scene::Scene&, std::string);
  XMFLOAT3        position;
  XMFLOAT3        rotation = XMFLOAT3(0, wi::math::PI, 0);
  bool            controllable;
  Layers          layerMask;
  float           targetRotHorizontal = 0.0f;
  wi::ecs::Entity model;
  std::string     stateCur      = "idle";
  std::string     statePrev     = "idle";
  wi::ecs::Entity humanoid      = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity expression    = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneNeck      = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneHead      = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneHandLeft  = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneHandRight = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneFootLeft  = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneFootRight = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneToesLeft  = wi::ecs::INVALID_ENTITY;
  wi::ecs::Entity boneToesRight = wi::ecs::INVALID_ENTITY;
};


class Game : public wi::RenderPath3D {
  bool                   debugDraws          = false;
  float                  slopeThreshold      = 0.2f;   // How much slopeiness will cause character to slide down instead of standing on it
  float                  gravity             = -30.0f;
  bool                   dynamicVoxelization = false;   // Set to true to revoxelize navigation every frame
  Character*             player              = nullptr;
  wi::vector<Character*> npcs;
  bool                   footprintsEnabled = false;
  wi::vector<wi::primitive::Capsule> characterCapsules;
  wi::VoxelGrid                      voxelGrid;
public:
  void Load() override;
  void Update(float dt) override;
};


class App : public wi::Application {
  Game game;
public:
  void Initialize() override;
};

extern App app;
