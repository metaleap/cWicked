#pragma once

#include "../pch/wi_pch.h"

#include "./cwicked.h"



class WiWrapApplication : public wi::Application {
public:
  void* overrides[_WI_ON_COUNT];
  WiApplicationOn0 onFixedUpdate;
  WiApplicationOn1 onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};



class WiWrapRenderPath2D : public wi::RenderPath2D {
public:
  void* ctx;
  WiRenderPathOnFixedUpdate onFixedUpdate;
  WiRenderPathOnUpdate onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};



class WiWrapRenderPath3D : public wi::RenderPath3D {
public:
  void* ctx;
  WiRenderPathOnFixedUpdate onFixedUpdate;
  WiRenderPathOnUpdate onUpdate;
  void FixedUpdate() override;
  void Update(float) override;
};
