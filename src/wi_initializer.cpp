#include "./wi.hpp"


void wi_initializer_waitForInitializationsToFinish() {
  return wi::initializer::WaitForInitializationsToFinish();
}

void wi_initializer_initializeComponentsAsync() {
  return wi::initializer::InitializeComponentsAsync();
}

void wi_initializer_initializeComponentsImmediate() {
  return wi::initializer::InitializeComponentsImmediate();
}

bool wi_initializer_isInitializeFinished(WI_INITIALIZED_SYSTEM system) {
  static_assert(((int)WI_INITIALIZED_SYSTEM_COUNT) == ((int)wi::initializer::INITIALIZED_SYSTEM_COUNT));
  return wi::initializer::IsInitializeFinished((wi::initializer::INITIALIZED_SYSTEM)(system));
}
