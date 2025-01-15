#pragma once

#include "../pch/wi_pch.h"

#include "./cwicked.h"



class WiWrapApplication : public wi::Application {
public:
  void* handlers[_WI_ON_COUNT];
  void FixedUpdate() override;
  void Update(float) override;
  void Initialize() override;
  void Render() override;
  void Compose(wi::graphics::CommandList cmd) override;
};



class WiWrapRenderPath3D : public wi::RenderPath3D {
public:
  void* handlers[_WI_ON_COUNT];
  void FixedUpdate() override;
  void Update(float) override;
  void PreUpdate() override;
  void PostUpdate() override;
  void Start() override;
  void Stop() override;
  void Load() override;
  void Render() const override;
  void Compose(wi::graphics::CommandList cmd) const override;
};
