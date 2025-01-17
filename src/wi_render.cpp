#include "./wi.hpp"



void wi_renderer_setShaderPath(char* path) {
  return wi::renderer::SetShaderPath(std::string(path));
}

void wi_renderer_setShaderSourcePath(char* path) {
  return wi::renderer::SetShaderSourcePath(std::string(path));
}



void WiWrapRenderPath3D::FixedUpdate() {
  wi::RenderPath3D::FixedUpdate();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_FIXEDUPDATE];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::PreUpdate() {
  wi::RenderPath3D::PreUpdate();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDERPATH_PREUPDATE];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::PostUpdate() {
  wi::RenderPath3D::PostUpdate();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDERPATH_POSTUPDATE];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::Load() {
  wi::RenderPath3D::Load();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDERPATH_LOAD];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::Start() {
  wi::RenderPath3D::Start();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDERPATH_START];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::Stop() {
  wi::RenderPath3D::Stop();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDERPATH_STOP];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::Update(float delta) {
  wi::RenderPath3D::Update(delta);
  auto handler = (WiRenderPathHandler1)this->handlers[WI_ON_UPDATE];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this), delta);
}

void WiWrapRenderPath3D::Render() const {
  wi::RenderPath3D::Render();
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_RENDER];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}

void WiWrapRenderPath3D::Compose(wi::graphics::CommandList cmdList) const {
  wi::RenderPath3D::Compose(cmdList);
  auto handler = (WiRenderPathHandler0)this->handlers[WI_ON_COMPOSE];
  if (handler != nullptr)
    handler((WiRenderPath3D)(this));
}



WiRenderPath3D WiRenderPath3D_new() {
  auto ret = new WiWrapRenderPath3D();
  for (int i = 0; i < _WI_ON_COUNT; i++)
    ret->handlers[i] = nullptr;
  return (WiRenderPath3D)(ret);
}

void WiRenderPath3D_dispose(WiRenderPath3D self) {
  delete ((WiWrapRenderPath3D*)(self));
}

void WiRenderPath3D_load(WiRenderPath3D self) {
  auto me = (WiWrapRenderPath3D*)(self);
  return me->Load();
}

void WiRenderPath3D_init(WiRenderPath3D self, SDL_Window* window) {
  auto me = (WiWrapRenderPath3D*)(self);
  return me->init(window);
}
