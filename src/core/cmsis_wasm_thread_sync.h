#ifndef _CMSIS_WASM_THREAD_SYNC_H_
#define _CMSIS_WASM_THREAD_SYNC_H_

#include "cmsis_wasm_queue.h"

extern osStatus_t PosixOsThreadSyncSleep(uint32_t timeout);

extern void *PosixOsThreadSyncWait(PosixOsQueueHeadType *waiting_queue, uint32_t timeout, osStatus_t*ercdp);
extern bool_t PosixOsThreadSyncWakeupFirstEntry(PosixOsQueueHeadType *waiting_queue, void *data, osStatus_t ercd);

extern void PosixOsThreadSyncInit(void);
extern void PosixOsThreadSyncLock(void);
extern void PosixOsThreadSyncUnlock(void);

#endif /* _CMSIS_WASM_THREAD_SYNC_H_ */
