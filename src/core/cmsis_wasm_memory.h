#ifndef _CMSIS_WASM_MEMORY_H_
#define _CMSIS_WASM_MEMORY_H_

#include "cmsis_wasm_common.h"

extern void *WasmMemoryAlloc(uint32_t size);
extern void WasmMemoryFree(void *addrp);

#endif /* _CMSIS_WASM_MEMORY_H_ */
