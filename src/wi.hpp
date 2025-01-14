#pragma once

#include "../pch/wi_pch.h"

#include "cWicked.h"



class WiWrapApplication : public wi::Application {
public:
  WiApplicationOnFixedUpdate onFixedUpdate;
  WiApplicationOnUpdate onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};



class WiWrapRenderPath3D : public wi::RenderPath3D {
public:
  void* ctx;
  WiRenderPath3DOnFixedUpdate onFixedUpdate;
  WiRenderPath3DOnUpdate onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};
