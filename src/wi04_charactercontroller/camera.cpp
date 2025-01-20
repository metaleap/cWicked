#include "./app.h"
#include ".wi/WickedEngine/wiECS.h"


ThirdPersonCamera::ThirdPersonCamera(Character* character) {
  this->character = character;
  this->camera    = wi::ecs::CreateEntity();
}
