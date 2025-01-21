#include "./app.h"



ThirdPersonCamera::ThirdPersonCamera(Character* character) {
  this->character  = character;
  this->cam_entity = wi::ecs::CreateEntity();
}



void ThirdPersonCamera::update(bool debugDraws) {
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
  auto mat           = XMMatrixTranslation(this->sideOffset, 0, -this->distanceRest);
  mat                = XMMatrixMultiply(mat, XMLoadFloat4x4(&target_transform.world));
  auto cam_transform = scene.transforms.GetComponent(this->cam_entity);
  assert(cam_transform != nullptr);
  cam_transform->ClearTransform();
  cam_transform->MatrixTransform(mat);
  cam_transform->UpdateTransform();

  // Camera collision:

  // Compute the relation vectors between camera and target:
  auto pos_cam    = cam_transform->GetPosition();
  auto pos_target = target_transform.GetPosition();
  auto dist_cam   = wi::math::Length(XMFLOAT3(pos_cam.x - pos_target.x, pos_cam.y - pos_target.y, -pos_cam.z - pos_target.z));

  // These will store the closest collision distance and required camera position:
  auto dist_best = dist_cam;
  auto pos_best  = pos_cam;
  auto cam       = wi::scene::GetCamera();

  // Update global camera matrices for rest position:
  cam.TransformCamera(*cam_transform);
  cam.UpdateCamera();

  // Cast rays from target to clip space points on the camera near plane to avoid clipping through objects:
  auto            unproj = cam.GetInvViewProjection();
  static XMVECTOR clip_coords[5]
      = {vec4From(0, 0, 1, 1), vec4From(-1, -1, 1, 1), vec4From(-1, 1, 1, 1), vec4From(1, -1, 1, 1), vec4From(1, 1, 1, 1)};
  for (int i = 0; i < 5; i++) {
    auto corner           = XMVector3TransformCoord(clip_coords[i], unproj);
    auto target_to_corner = XMVectorSubtract(corner, vec4From(pos_target.x, pos_target.y, pos_target.z, 0));
    auto corner_to_campos = XMVectorSubtract(vec4From(pos_cam.x, pos_cam.y, pos_cam.z, 0), corner);

    auto tmax       = XMVectorGetX(XMVector3Length(target_to_corner));   // optimization: limit the ray tracing distance
    auto ray        = wi::primitive::Ray(vec4From(pos_target.x, pos_target.y, pos_target.z, 0), XMVector3Normalize(target_to_corner), 0, tmax);
    auto coll_layer = ~(Layers::Player | Layers::Npc);
    auto intersects = scene.Intersects(ray, wi::enums::FILTER::FILTER_NAVIGATION_MESH | wi::enums::FILTER::FILTER_COLLIDER, coll_layer);
    if (intersects.entity != wi::ecs::INVALID_ENTITY) {   // hit something, see if it is between the player and camera:
      auto coll_diff
          = XMFLOAT3(intersects.position.x - pos_target.x, intersects.position.y - pos_target.y, intersects.position.z - pos_target.z);
      auto coll_dist = wi::math::Length(coll_diff);
      if ((coll_dist > 0) && (coll_dist < dist_best)) {
        dist_best = coll_dist;
        auto add  = vec3To(corner_to_campos);
        pos_best  = XMFLOAT3(intersects.position.x + add.x, intersects.position.y + add.y, intersects.position.z + add.z);
        if (debugDraws)
          wi::renderer::DrawPoint(wi::renderer::RenderablePoint {.position = intersects.position, .size = 0.1f, .color = XMFLOAT4(1, 0, 0, 1)});
      }
    }
  }

  // We have the best candidate for new camera position now, so offset the camera with the delta between the old and new camera position:
  auto coll_offset = XMFLOAT3(pos_best.x - pos_cam.x, pos_best.y - pos_cam.y, pos_best.z - pos_cam.z);
  mat              = XMMatrixMultiply(mat, XMMatrixTranslation(coll_offset.x, coll_offset.y, coll_offset.z));
  cam_transform->ClearTransform();
  cam_transform->MatrixTransform(mat);
  cam_transform->UpdateTransform();
  if (debugDraws)
    wi::renderer::DrawPoint(wi::renderer::RenderablePoint {.position = pos_best, .size = 0.1f, .color = XMFLOAT4(1, 1, 0, 1)});

  // Feed back camera after collision:
  cam.TransformCamera(*cam_transform);
  cam.UpdateCamera();
}
