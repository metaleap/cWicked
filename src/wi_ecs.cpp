#include "./wi.hpp"




WiEntity WiEntity_create() {
  return wi::ecs::CreateEntity();
}

WiComponentManager WiComponentManager_new(size_t reservedCount) {
  return new wi::ecs::ComponentManager<WiComponent>(reservedCount);
}

WiComponent WiComponentManager_create(WiComponentManager self, WiEntity entity) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->Create((wi::ecs::Entity)(entity));
}

void WiComponent::Serialize(wi::Archive&, wi::ecs::EntitySerializer&) {
}

void WiComponentManager_clear(WiComponentManager self) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->Clear();
}

void WiComponentManager_remove(WiComponentManager self, WiEntity entity) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->Remove((wi::ecs::Entity)(entity));
}

WiComponent* WiComponentManager_getComponent(WiComponentManager self, WiEntity entity) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  auto ret = me->GetComponent((wi::ecs::Entity)(entity));
  return ret;
}

size_t WiComponentManager_getCount(WiComponentManager self) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->GetCount();
}

void WiComponentManager_forEachComponent(WiComponentManager self, WiComponentFunc handler) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  for (WiComponent it : me->GetComponentArray())
    handler(it);
}

void WiComponentManager_forEachEntity(WiComponentManager self, WiEntityFunc handler) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  for (WiEntity it : me->GetEntityArray())
    handler(it);
}

bool WiComponentManager_contains(WiComponentManager self, WiEntity entity) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->Contains((wi::ecs::Entity)(entity));
}

size_t WiComponentManager_getIndex(WiComponentManager self, WiEntity entity) {
  auto me = (wi::ecs::ComponentManager<WiComponent>*)(self);
  return me->GetIndex((wi::ecs::Entity)(entity));
}
