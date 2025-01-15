#include "./wi.hpp"
#include ".wi/WickedEngine/wiSDLInput.h"



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
  assert(sizeof(WiMouseState) == sizeof(wi::input::MouseState));
  auto ret = wi::input::GetMouseState();
  return (WiMouseState*)(&ret); // ignore Wreturn-stack-address: it's a static in wiInput.cpp
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

void wi_input_sdlInput_processEvent(SDL_Event* evt) {
  return wi::input::sdlinput::ProcessEvent(*evt);
}

void wi_input_sdlInput_getKeyboadState(WiKeyboardState* state) {
  assert(sizeof(WiKeyboardState) == sizeof(wi::input::KeyboardState));
  return wi::input::sdlinput::GetKeyboardState((wi::input::KeyboardState*)(state));
}

void wi_input_sdlInput_getMouseState(WiMouseState* state) {
  assert(sizeof(WiMouseState) == sizeof(wi::input::MouseState));
  return wi::input::sdlinput::GetMouseState((wi::input::MouseState*)(state));
}

// void wi_input_sdlInput_setControllerFeedback() {
//   return wi::input::sdlinput::SetControllerFeedback();
// }
