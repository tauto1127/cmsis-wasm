#ifndef _CMSIS_WASM_THREAD_SYNC_H_
#define _CMSIS_WASM_THREAD_SYNC_H_

#include "cmsis_wasm_queue.h"

extern osStatus_t WasmThreadSyncSleep(uint32_t timeout);

extern void *WasmThreadSyncWait(WasmQueueHeadType *waiting_queue, uint32_t timeout, osStatus_t*ercdp);
extern bool_t WasmThreadSyncWakeupFirstEntry(WasmQueueHeadType *waiting_queue, void *data, osStatus_t ercd);

extern void WasmThreadSyncInit(void);
extern void WasmThreadSyncLock(void);
extern void WasmThreadSyncUnlock(void);

#endif /* _CMSIS_WASM_THREAD_SYNC_H_ */
