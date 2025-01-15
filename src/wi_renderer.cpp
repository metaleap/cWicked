#include "./wi.hpp"



void WiWrapRenderPath3D::FixedUpdate() {
  wi::RenderPath3D::FixedUpdate();
  if (this->onFixedUpdate != nullptr)
    this->onFixedUpdate(this->ctx);
}

void WiWrapRenderPath3D::Update(float delta) {
  wi::RenderPath3D::Update(delta);
  if (this->onUpdate != nullptr)
    this->onUpdate(this->ctx, delta);
}



void wi_renderer_setShaderPath(char* path) {
  return wi::renderer::SetShaderPath(std::string(path));
}

void wi_renderer_setShaderSourcePath(char* path) {
  return wi::renderer::SetShaderSourcePath(std::string(path));
}

WiRenderPath3D wi_RenderPath3D_new(void* ctx, WiRenderPathOnFixedUpdate onFixedUpdate, WiRenderPathOnUpdate onUpdate) {
  auto ret = new WiWrapRenderPath3D();
  ret->ctx = ctx;
  ret->onFixedUpdate = onFixedUpdate;
  ret->onUpdate = onUpdate;
  return (WiRenderPath3D)(ret);
}

void wi_RenderPath3D_dispose(WiRenderPath3D app) {
  delete ((WiWrapRenderPath3D*)(app));
}
