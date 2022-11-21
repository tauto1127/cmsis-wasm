#include "cmsis_wasm_time.h"

static uint64_t wasm_activated_time64;

static uint64_t wasm_get_current_time(void)
{
  struct timespec tmo;
  clock_gettime(CLOCK_REALTIME, &tmo);
  uint64_t sec = tmo.tv_sec;
  uint64_t msec = (tmo.tv_nsec / (TIMESPEC_MSEC * TIMESPEC_MSEC));
  uint64_t ticks = (sec * TIMESPEC_MSEC) + msec;
  return ticks;
}

osStatus_t PosixOsTimerInit(void)
{
  if (wasm_activated_time64 != 0) {
    return osError;
  }
  wasm_activated_time64 = wasm_get_current_time();
  return osOK;
}

uint32_t PosixOsTimeGetTickCount(void)
{
  uint64_t ctime64 = wasm_get_current_time();
  uint64_t ctime64_relative = ctime64 - wasm_activated_time64;
  return ((uint32_t)ctime64_relative);
}
