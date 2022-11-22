#include "cmsis_wasm_memory.h"

void* WasmMemoryAlloc(uint32_t size)
{
  void* addrp = NULL;

  if (CurrentContextIsISR()) {
    return NULL;
  }
  addrp = malloc(size);
  return addrp;
}

void WasmMemoryFree(void* addrp)
{
  if (CurrentContextIsISR()) {
    return;
  }
  if (addrp != NULL) {
    free(addrp);
  }
  return;
}
