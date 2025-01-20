#pragma once

#include "../../pch/wi_min_pch.h"


#define CC_DIR_PATH "../../.wi/Content/scripts/character_controller/"



class Character {
public:
};


class Game : public wi::RenderPath3D {
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
  Game game;
public:
  void Initialize() override;
};



enum Layers : uint32_t {
  Player = 1 << 0,   // 1
  Npc    = 1 << 1,   // 2
};



App  app;
Game rend;
