#include "./app.h"


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
    auto entity = scene.expressions.GetEntity(i);
    if (scene.Entity_IsDescendant(entity, this->model)) {
      this->expression = entity;
      // Set up some overrides to avoid bad looking expression combinations:
      auto expr        = &scene.expressions[i];
      exprOverride(expr, wi::scene::ExpressionComponent::Preset::Happy, wi::scene::ExpressionComponent::Override::Block, true, false, false);
      exprOverride(expr, wi::scene::ExpressionComponent::Preset::Happy, wi::scene::ExpressionComponent::Override::Blend, false, false, true);
      exprOverride(expr, wi::scene::ExpressionComponent::Preset::Surprised, wi::scene::ExpressionComponent::Override::Block, true, false,
                   false);
    }
  }

  // Enable wetmap for all objects of character, so it can get wet in the ocean (if the weather has it)
  for (size_t i = 0; i < scene.objects.GetCount(); i++) {
    auto entity = scene.objects.GetEntity(i);
    if (scene.Entity_IsDescendant(entity, this->model)) {
      auto obj = &scene.objects[i];
      obj->SetWetmapEnabled(true);
      this->objectEntities.push_back(entity);
    }
  }

  // Create a base capsule collider for character:
  wi::scene::ColliderComponent& coll = scene.colliders.Create(this->model);
  coll.SetCPUEnabled(false);
  coll.SetGPUEnabled(true);
  coll.shape  = wi::scene::ColliderComponent::Shape::Capsule;
  coll.radius = character_component.width;
  coll.offset = XMFLOAT3(0, coll.radius, 0);
  coll.tail   = XMFLOAT3(0, character_component.height - coll.radius, 0);
  auto head   = scene.transforms.GetComponent(this->boneHead);
  if (head != nullptr)
    coll.tail = head->GetPosition();
  this->root = this->humanoid;
  scene.ResetPose(this->model);

  // The base animation entities are queried from the anim_scene, they are not yet targeting our character:
  this->anims["idle"]      = animScene.Entity_FindByName("idle");
  this->anims["walk"]      = animScene.Entity_FindByName("walk");
  this->anims["jog"]       = animScene.Entity_FindByName("jog");
  this->anims["run"]       = animScene.Entity_FindByName("run");
  this->anims["jump"]      = animScene.Entity_FindByName("jump");
  this->anims["swim_idle"] = animScene.Entity_FindByName("swim_idle");
  this->anims["swim"]      = animScene.Entity_FindByName("swim");
  this->anims["dance"]     = animScene.Entity_FindByName("dance");
  this->anims["wave"]      = animScene.Entity_FindByName("wave");

  // Retarget animation entities onto the character, and add them to the CharacterComponent:
  // Also see if a requested animation set (animset) is available for each animation, and use that instead if yes
  animSet = "_" + animSet;
  for (auto pair : this->anims) {
    std::string     anim_state          = pair.first;
    wi::ecs::Entity anim_entity         = pair.second;
    auto            anim_name_component = animScene.names.GetComponent(anim_entity);
    if (anim_name_component != nullptr) {
      auto anim_set_name   = anim_name_component->name + animSet;
      auto anim_set_entity = animScene.Entity_FindByName(anim_set_name);
      if (anim_set_entity != wi::ecs::INVALID_ENTITY)
        anim_entity = anim_set_entity;
      this->anims[anim_state] = scene.RetargetAnimation(this->humanoid, anim_entity, false, &animScene);
      character_component.AddAnimation(this->anims[anim_state]);
    }
  }

  auto model_transform = scene.transforms.GetComponent(this->model);
  model_transform->ClearTransform();
  model_transform->Scale(this->scale);
  model_transform->Rotate(XMFLOAT4(this->rotation.x, this->rotation.y, this->rotation.z, 0));
  model_transform->Translate(this->position);
  model_transform->UpdateTransform();

  this->targetHeight = scene.transforms.GetComponent(this->boneNeck)->GetPosition().y;
}


XMFLOAT3 Character::getFacing() {
  return wi::scene::GetScene().characters.GetComponent(this->model)->GetFacingSmoothed();
}


void Character::jump(float amount) {
  this->state = "jump";
  return wi::scene::GetScene().characters.GetComponent(this->model)->Jump(amount);
}


void Character::turn(XMFLOAT3& direction) {
  return wi::scene::GetScene().characters.GetComponent(this->model)->Turn(direction);
}


void Character::moveDir(XMFLOAT3& direction) {
  auto character_component = wi::scene::GetScene().characters.GetComponent(this->model);
  auto rotation_matrix     = XMMatrixMultiply(XMMatrixRotationY(this->targetRotHorizontal), XMMatrixRotationX(this->targetRotVertical));
  auto dir                 = XMVector3TransformNormal(XMVector3Normalize(vec3From(direction)), rotation_matrix);
  direction                = vec3To(dir);
  direction.y              = 0;
  character_component->Turn(direction);

  auto speed = this->speedWalking;
  if (this->state == "jog")
    speed = this->speedJogging;
  else if (this->state == "run")
    speed = this->speedRunning;
  else if (this->state == "swim")
    speed = this->speedSwimming;
  auto tmp = this->getFacing();
  character_component->Move(XMFLOAT3(tmp.x * speed, tmp.y * speed, tmp.z * speed));
}


void Character::setAnimationAmount(float amount) {
  return wi::scene::GetScene().characters.GetComponent(this->model)->SetAnimationAmount(amount);
}


void Character::update(float delta) {
}
