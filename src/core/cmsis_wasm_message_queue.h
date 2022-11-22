#ifndef _CMSIS_WASM_MESSAGE_QUEUE_H_
#define _CMSIS_WASM_MESSAGE_QUEUE_H_

#include "cmsis_wasm_queue.h"

/***********************************************
 *
 * MESSAGE QUEUE
 *
 ***********************************************/
#define MESSAGE_QUEUE_ENTRY_ALIGNMENT_SIZE	4U
#define MESSAGE_QUEUE_ENTRY_ALIGNED_SIZE(size)	\
	(	\
			(	\
				(	\
						(size) + (MESSAGE_QUEUE_ENTRY_ALIGNMENT_SIZE - 1)	\
				)	\
				/ MESSAGE_QUEUE_ENTRY_ALIGNMENT_SIZE	\
			)	\
			* MESSAGE_QUEUE_ENTRY_ALIGNMENT_SIZE	\
	)


#define WASM_MESSAGE_QUEUE_HEAD_MAGICNO		0xDEAFBEAD
typedef struct {
  uint16_t			prealloc_num;
  uint16_t			entry_size;
  uint32_t			magicno;
  WasmQueueHeadType	used;
  WasmQueueHeadType	free;
  WasmQueueHeadType	getter_waiting;
  WasmQueueHeadType	putter_waiting;
} WasmMessageQueueType;


typedef struct {
  CMSIS_IMPL_QUEUE						queue;
  /*
   * Priority
   *
   *  Highest  UINT16_MAX
   *  Lowest   0
   */
  uint16_t					prio;
  void* data;
} WasmMessageQueueEntryType;


typedef struct {
  uint16_t 					prealloc_num;
  uint16_t 					entry_size;
  WasmMessageQueueEntryType* control_datap;
  void* entries_datap;
} WasmMessageQueueConfigType;
extern WasmMessageQueueType* WasmMessageQueueCreate(WasmMessageQueueConfigType* config);
extern osStatus_t WasmMessageQueueDelete(WasmMessageQueueType* qh);

extern osStatus_t WasmMessageQueueGet(WasmMessageQueueType* qh, void* msg_ptr, uint8_t* msg_prio, uint32_t timeout);
extern osStatus_t WasmMessageQueuePut(WasmMessageQueueType* qh, const void* msg_ptr, uint8_t msg_prio, uint32_t timeout);
extern bool_t WasmMessageQueueIsValid(WasmMessageQueueType* qh);

#endif /* _CMSIS_WASM_MESSAGE_QUEUE_H_ */
