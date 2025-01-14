#include "./wi.hpp"


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
  wi::initializer::WaitForInitializationsToFinish();
}
