#ifndef _CMSIS_WASM_QUEUE_H_
#define _CMSIS_WASM_QUEUE_H_

#include "cmsis_wasm_common.h"

typedef struct {
  uint16_t	count;
  CMSIS_IMPL_QUEUE		*entries;
} WasmQueueHeadType;

#define WasmQueueHeadInitializer(var)	\
		WasmQueueHeadType var = { .count = 0, .entries = NULL }
#define WasmQueueHeadInit(qheadp)	\
do {	\
	(qheadp)->count = 0;	\
	(qheadp)->entries = NULL;	\
} while (0)

extern void WasmQueueHeadAddTail(WasmQueueHeadType *headp, CMSIS_IMPL_QUEUE *entry);
extern CMSIS_IMPL_QUEUE* WasmQueueHeadRemoveFirst(WasmQueueHeadType *headp);
extern void WasmQueueHeadRemoveEntry(WasmQueueHeadType *headp, CMSIS_IMPL_QUEUE *entry);

#endif /* _CMSIS_WASM_QUEUE_H_ */
