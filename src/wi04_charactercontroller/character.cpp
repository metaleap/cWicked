#include "./app.h"
#include ".wi/WickedEngine/LUA/lua.h"
#include ".wi/WickedEngine/Utility/DirectXMath.h"
#include ".wi/WickedEngine/wiMath.h"
#include ".wi/WickedEngine/wiScene.h"
#include ".wi/WickedEngine/wiScene_Components.h"
#include <cstddef>


static XMVECTOR vec3From(XMFLOAT3 v) {
  return XMLoadFloat3(&v);
}
static XMVECTOR vec3From(float x, float y, float z) {
  return vec3From(XMFLOAT3(x, y, z));
}
static XMFLOAT3 vec3To(XMVECTOR it) {
  XMFLOAT3 ret;
  XMStoreFloat3(&ret, it);
  return ret;
}

static void exprOverride(wi::scene::ExpressionComponent* it, wi::scene::ExpressionComponent::Preset preset,
                         wi::scene::ExpressionComponent::Override override, bool overrideBlink, bool overrideLook, bool overrideMouth) {
  if (it != nullptr) {
    size_t idx = it->presets[(size_t) preset];
    if ((idx >= 0) && (it->expressions.size() > idx)) {
      if (overrideBlink)
        it->expressions[idx].override_blink = override;
      if (overrideLook)
        it->expressions[idx].override_look = override;
      if (overrideMouth)
        it->expressions[idx].override_mouth = override;
    }
  }
}


Character::Character(wi::scene::Scene* model, wi::scene::TransformComponent* startTransform, bool controllable, wi::scene::Scene& animScene,
                     std::string animSet) {
  this->position = startTransform->GetPosition();
  auto facing = XMVector3Rotate(vec3From(startTransform->GetForward()), XMQuaternionRotationRollPitchYawFromVector(vec3From(this->rotation)));
  this->controllable = controllable;
  if (this->controllable) {
    this->layerMask           = Layers::Player;
    this->targetRotHorizontal = wi::math::GetAngle(vec3From(0, 0, 1), facing, vec3From(0, 1, 0));   // only modify camera rot for player
  } else
    this->layerMask = Layers::Npc;

  wi::scene::Scene& scene = wi::scene::GetScene();
  // `startTransform` ptr becomes invalid after this:
  this->model             = scene.Instantiate(*model, true);

  wi::scene::CharacterComponent& character_component = scene.characters.Create(this->model);
  character_component.SetPosition(this->position);
  character_component.SetFacing(vec3To(facing));
  character_component.width  = 0.321f;
  character_component.height = 1.77f;

  auto layer       = scene.layers.GetComponent(this->model);
  layer->layerMask = this->layerMask;

  for (size_t i = 0; i < scene.humanoids.GetCount(); i++) {
    auto entity = scene.humanoids.GetEntity(i);
    if (scene.Entity_IsDescendant(entity, this->model)) {
      this->humanoid = entity;
      auto hum       = scene.humanoids.GetComponent(this->humanoid);
      hum->SetLookAtEnabled(false);
      this->boneNeck      = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::Neck];
      this->boneHead      = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::Head];
      this->boneFootLeft  = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::LeftFoot];
      this->boneFootRight = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::RightFoot];
      this->boneHandLeft  = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::LeftHand];
      this->boneHandRight = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::RightHand];
      this->boneToesLeft  = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::LeftToes];
      this->boneToesRight = hum->bones[(size_t) wi::scene::HumanoidComponent::HumanoidBone::RightToes];
      break;
    }
  }
  for (size_t i = 0; i < scene.expressions.GetCount(); i++) {
    auto entity = scene.humanoids.GetEntity(i);
    if (scene.Entity_IsDescendant(entity, this->model)) {
      this->expression = entity;
      // Set up some overrides to avoid bad looking expression combinations:
      exprOverride(scene.expressions.GetComponent(this->expression), wi::scene::ExpressionComponent::Preset::Happy,
                   wi::scene::ExpressionComponent::Override::Block, true, false, false);
      exprOverride(scene.expressions.GetComponent(this->expression), wi::scene::ExpressionComponent::Preset::Happy,
                   wi::scene::ExpressionComponent::Override::Blend, false, false, true);
      exprOverride(scene.expressions.GetComponent(this->expression), wi::scene::ExpressionComponent::Preset::Surprised,
                   wi::scene::ExpressionComponent::Override::Block, true, false, false);
    }
  }

  // Enable wetmap for all objects of character, so it can get wet in the ocean (if the weather has it)
}
