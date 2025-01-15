#include "./wi.hpp"
#include ".wi/WickedEngine/wiJobSystem.h"
#include "src/copied.h"
#include <cstdint>



WiJobContext WiJobContext_create() {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto ret = wi::jobsystem::context();
  return *((WiJobContext*)(&ret));
}

void wi_jobsystem_dispatch(WiJobContext* ctx, uint32_t jobCount, uint32_t groupSize, WiJobHandler handler) {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  wi::jobsystem::Dispatch(*((wi::jobsystem::context*)(ctx)), jobCount, groupSize, [&](wi::jobsystem::JobArgs args) {
    static_assert(sizeof(WiJobArgs) == sizeof(wi::jobsystem::JobArgs));
    return handler((WiJobArgs*)(&args));
  });
}
