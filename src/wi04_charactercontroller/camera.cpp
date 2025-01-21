#include "./app.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiMath.h"
#include ".wi/WickedEngine/wiScene.h"
#include ".wi/WickedEngine/wiScene_Components.h"


ThirdPersonCamera::ThirdPersonCamera(Character* character) {
  this->character = character;
  this->camera    = wi::ecs::CreateEntity();
}


void ThirdPersonCamera::update(float delta) {
  if (this->character == nullptr)
    return;
  wi::scene::Scene& scene = wi::scene::GetScene();

  // Mouse scroll or gamepad triggers will move the camera distance:
  auto scroll           = this->zoomSpeed + wi::input::GetPointer().z;                       // mouse wheel delta this frame
  this->distanceRestNew = std::max(this->distanceMin, this->distanceRestNew - scroll);       // dont allow too close
  this->distanceRest    = wi::math::Lerp(this->distanceRest, this->distanceRestNew, 0.1f);   // smooth out the zooming

  // some smoothing for certain movements of camera target
  auto character_transform = scene.transforms.GetComponent(this->character->model);
  auto character_pos       = character_transform->GetPosition();
  this->targetRotH         = wi::math::Lerp(this->targetRotH, this->character->camTargetRotH, 0.1f);
  this->targetRotV         = wi::math::Lerp(this->targetRotV, this->character->camTargetRotV, 0.1f);
  this->targetHeight
      = wi::math::Lerp(this->targetHeight, character_pos.y + this->character->camTargetHeight + this->character->camRootOffset, 0.1f);

  auto target_transform = wi::scene::TransformComponent();
  target_transform.Translate(XMFLOAT3(character_pos.x, 0, character_pos.z));
  target_transform.Translate(XMFLOAT3(0, this->targetHeight, 0));   // TODO < ^
  target_transform.Rotate(XMFLOAT4(this->targetRotV, this->targetRotH, 0, 0));
  target_transform.UpdateTransform();

  // First calculate the rest orientation (transform) of the camera:
  auto mat              = XMMatrixTranslation(this->sideOffset, 0, -this->distanceRest);
  mat                   = XMMatrixMultiply(mat, XMLoadFloat4x4(&target_transform.world));
  auto camera_transform = scene.transforms.GetComponent(this->camera);
  camera_transform->ClearTransform();
  camera_transform->MatrixTransform(mat);
  camera_transform->UpdateTransform();

  // Camera collision:
}
