#include "./wi.hpp"



void wi_input_clearForNextFrame() {
  return wi::input::ClearForNextFrame();
}

bool wi_input_down(WI_BUTTON button, int playerIndex) {
  static_assert(((int)WI_BUTTON_ENUM_SIZE) == ((int)wi::input::BUTTON::BUTTON_ENUM_SIZE));
  return wi::input::Down((wi::input::BUTTON)button, playerIndex);
}

bool wi_input_hold(WI_BUTTON button, uint32_t frames, bool continuous, int playerIndex) {
  static_assert(((int)WI_BUTTON_ENUM_SIZE) == ((int)wi::input::BUTTON::BUTTON_ENUM_SIZE));
  return wi::input::Hold((wi::input::BUTTON)button, frames, continuous, playerIndex);
}

WI_BUTTON wi_input_whatIsPressed(int playerIndex) {
  static_assert(((int)WI_BUTTON_ENUM_SIZE) == ((int)wi::input::BUTTON::BUTTON_ENUM_SIZE));
  return (WI_BUTTON)(wi::input::WhatIsPressed(playerIndex));
}

WI_XMFLOAT4 wi_input_getAnalog(WI_GAMEPAD_ANALOG analog, int playerIndex) {
  static_assert(sizeof(WI_XMFLOAT4) == sizeof(XMFLOAT4));
  auto tmp = (wi::input::GetAnalog((wi::input::GAMEPAD_ANALOG)analog, playerIndex));
  return *((WI_XMFLOAT4*)(&tmp));
}

bool wi_input_isGamepadButton(WI_BUTTON button) {
  static_assert(((int)WI_BUTTON_ENUM_SIZE) == ((int)wi::input::BUTTON::BUTTON_ENUM_SIZE));
  return wi::input::IsGamepadButton((wi::input::BUTTON)button);
}

WiMouseState* wi_input_getMouseState() {
  static_assert(sizeof(WiMouseState) == sizeof(wi::input::MouseState));
  const wi::input::MouseState& ret = wi::input::GetMouseState(); // reference to a static in wiInput.cpp, hence:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
  return (WiMouseState*)(&ret);
#pragma GCC diagnostic pop
}

bool wi_input_press(WI_BUTTON button, int playerIndex) {
  static_assert(((int)WI_BUTTON_ENUM_SIZE) == ((int)wi::input::BUTTON::BUTTON_ENUM_SIZE));
  return wi::input::Press((wi::input::BUTTON)button, playerIndex);
}

WI_XMFLOAT4 wi_input_getPointer() {
  static_assert(sizeof(WI_XMFLOAT4) == sizeof(XMFLOAT4));
  auto tmp = wi::input::GetPointer();
  return *((WI_XMFLOAT4*)(&tmp));
}

void wi_input_update(SDL_Window* window, WiCanvas* canvas) {
  static_assert((sizeof(WiCanvas) + 8) == sizeof(wi::Canvas));
  return wi::input::Update(window, *(wi::Canvas*)(canvas));
}

void wi_input_sdlInput_processEvent(SDL_Event* evt) {
  return wi::input::sdlinput::ProcessEvent(*evt);
}

void wi_input_sdlInput_getKeyboadState(WiKeyboardState* state) {
  static_assert(sizeof(WiKeyboardState) == sizeof(wi::input::KeyboardState));
  return wi::input::sdlinput::GetKeyboardState((wi::input::KeyboardState*)(state));
}

void wi_input_sdlInput_getMouseState(WiMouseState* state) {
  static_assert(sizeof(WiMouseState) == sizeof(wi::input::MouseState));
  return wi::input::sdlinput::GetMouseState((wi::input::MouseState*)(state));
}

void wi_input_sdlInput_getControllerState(WiControllerState* state, int index) {
  static_assert(sizeof(WiControllerState) == sizeof(wi::input::ControllerState));
  wi::input::sdlinput::GetControllerState((wi::input::ControllerState*)(state), index);
}

void wi_input_sdlInput_setControllerFeedback(WiControllerFeedback* data, int index) {
  static_assert(sizeof(WiControllerFeedback) == sizeof(wi::input::ControllerFeedback));
  auto tmp = (wi::input::ControllerFeedback*)(data);
  return wi::input::sdlinput::SetControllerFeedback(*tmp, index);
}

int wi_input_sdlInput_getMaxControllerCount() {
  wi::input::sdlinput::Update();
  return wi::input::sdlinput::GetMaxControllerCount();
}

void wi_input_sdlInput_update() {
  return wi::input::sdlinput::Update();
}
