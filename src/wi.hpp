#pragma once

#include "../pch/wi_pch.h"

#include "./cwicked.h"



class WiWrapApplication : public wi::Application {
public:
  WiApplicationOnFixedUpdate onFixedUpdate;
  WiApplicationOnUpdate onUpdate;
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
