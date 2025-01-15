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
  return wi::arguments::Parse(argc, argv);
}

bool wi_arguments_hasArgument(char* name) {
  return wi::arguments::HasArgument(name);
}

void WiRect_fromViewport(WiRect* rect, WiViewport* viewport) {
  static_assert((sizeof(WiRect)) == (sizeof(wi::graphics::Rect)));
  static_assert((sizeof(WiViewport)) == (sizeof(wi::graphics::Viewport)));
  wi::graphics::Rect* r = (wi::graphics::Rect*)rect;
  wi::graphics::Viewport* vp = (wi::graphics::Viewport*)viewport;
  return r->from_viewport(*vp);
}
