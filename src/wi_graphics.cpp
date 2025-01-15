#include "./wi.hpp"
#include ".wi/WickedEngine/wiGraphics.h"



void WiRect_fromViewport(WiRect* rect, WiViewport* viewport) {
  static_assert((sizeof(WiRect)) == (sizeof(wi::graphics::Rect)));
  static_assert((sizeof(WiViewport)) == (sizeof(wi::graphics::Viewport)));
  wi::graphics::Rect* r = (wi::graphics::Rect*)rect;
  wi::graphics::Viewport* vp = (wi::graphics::Viewport*)viewport;
  return r->from_viewport(*vp);
}
