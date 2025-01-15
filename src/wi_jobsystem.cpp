#include "./wi.hpp"



WiJobContext WiJobContext_create() {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto ret = wi::jobsystem::context();
  return *((WiJobContext*)(&ret));
}

void wi_jobsystem_dispatch(WiJobContext* ctx, uint32_t jobCount, uint32_t groupSize, WiJobHandler handler) {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto tmp = *((wi::jobsystem::context*)(ctx));
  wi::jobsystem::Dispatch(tmp, jobCount, groupSize, [&](wi::jobsystem::JobArgs args) {
    static_assert(sizeof(WiJobArgs) == sizeof(wi::jobsystem::JobArgs));
    return handler((WiJobArgs*)(&args));
  });
  *ctx = *((WiJobContext*)(&tmp));
}

void wi_jobsystem_execute(WiJobContext* ctx, WiJobHandler handler) {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto tmp = *((wi::jobsystem::context*)(ctx));
  wi::jobsystem::Execute(tmp, [&](wi::jobsystem::JobArgs args) {
    static_assert(sizeof(WiJobArgs) == sizeof(wi::jobsystem::JobArgs));
    return handler((WiJobArgs*)(&args));
  });
  *ctx = *((WiJobContext*)(&tmp));
}

void wi_jobsystem_wait(WiJobContext* ctx) {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto tmp = *((wi::jobsystem::context*)(ctx));
  return wi::jobsystem::Wait(tmp);
}

bool wi_jobsystem_isBusy(WiJobContext* ctx) {
  static_assert(sizeof(WiJobContext) == sizeof(wi::jobsystem::context));
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  auto tmp = *((wi::jobsystem::context*)(ctx));
  return wi::jobsystem::IsBusy(tmp);
}

uint32_t wi_jobsystem_getThreadCount(WiJobPriority priority) {
  static_assert(((int)(WI_JOBPRIORITY_COUNT)) == ((int)(wi::jobsystem::Priority::Count)));
  return wi::jobsystem::GetThreadCount((wi::jobsystem::Priority)(priority));
}
