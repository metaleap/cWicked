#include "./wi.hpp"
#include ".wi/WickedEngine/wiECS.h"




WiEntity WiEntity_create() {
  return wi::ecs::CreateEntity();
}
