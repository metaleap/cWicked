#include "./wi.hpp"
#include ".wi/WickedEngine/wiSDLInput.h"
#include <SDL_events.h>


const char* wi_version_getVersionString() {
  return wi::version::GetVersionString();
}

const char* wi_version_getCreditsString() {
  return wi::version::GetCreditsString();
}

int wi_version_getMajor() {
  return wi::version::GetMajor();
}

int wi_version_getMinor() {
  return wi::version::GetMinor();
}

int wi_version_getRevision() {
  return wi::version::GetRevision();
}

void wi_arguments_parse(int argc, char** argv) {
  wi::arguments::Parse(argc, argv);
}

void wi_initializer_waitForInitializationsToFinish() {
  // wi::input::sdlinput::ProcessEvent(const SDL_Event &event);
  wi::initializer::WaitForInitializationsToFinish();
}

void wi_input_sdlInput_processEvent(SDL_Event* evt) {
  wi::input::sdlinput::ProcessEvent(*evt);
}
