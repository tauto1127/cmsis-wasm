#include "cmsis_wasm_message_queue.h"
#include "cmsis_wasm_memory.h"
#include "cmsis_wasm_thread_sync.h"
#include <string.h>

WasmMessageQueueType* WasmMessageQueueCreate(WasmMessageQueueConfigType* config)
{
  uint32_t i;
  uint32_t entry_total_size;
  uint32_t msg_data_total_size;
  char* top;
  char* entry_top;
  char* msg_top;
  WasmMessageQueueType* qh;

  entry_total_size = sizeof(WasmMessageQueueEntryType) * config->prealloc_num;
  msg_data_total_size = config->entry_size * config->prealloc_num;

  top = WasmMemoryAlloc(sizeof(WasmMessageQueueType) + entry_total_size + msg_data_total_size);
  if (top == NULL) {
    CMSIS_IMPL_ERROR("ERROR:%s %s() %d cannot allocate memory size=%ld\n", __FILE__, __FUNCTION__, __LINE__, sizeof(WasmMessageQueueType) + entry_total_size + msg_data_total_size);
    return NULL;
  }
  qh = (WasmMessageQueueType*)top;
  qh->entry_size = config->entry_size;
  qh->prealloc_num = config->prealloc_num;
  qh->magicno = WASM_MESSAGE_QUEUE_HEAD_MAGICNO;
  WasmQueueHeadInit(&qh->free);
  WasmQueueHeadInit(&qh->used);
  WasmQueueHeadInit(&qh->getter_waiting);
  WasmQueueHeadInit(&qh->putter_waiting);

  entry_top = &top[sizeof(WasmMessageQueueType)];
  msg_top = &entry_top[entry_total_size];
  /*
   *  [ queue memory image ]
   *
   *     qh     entry0 entry1   .................  entryN    msg0     msg1      ...................     msgN
   *   |------|------|------|------|------|------|------|----------|----------|----------|----------|----------|
   */
  WasmMessageQueueEntryType* entry = (WasmMessageQueueEntryType*)entry_top;
  for (i = 0; i < qh->prealloc_num; i++) {
    entry->prio = 0;
    entry->data = &msg_top[i * qh->entry_size];
    WasmQueueHeadAddTail(&qh->free, &entry->queue);
    entry++;
  }
  return qh;
}

osStatus_t WasmMessageQueueDelete(WasmMessageQueueType* qh)
{
  if (qh == NULL) {
    return osErrorParameter;
  } else if (qh->magicno != WASM_MESSAGE_QUEUE_HEAD_MAGICNO) {
    return osErrorParameter;
  }
  qh->magicno = 0;
  WasmMemoryFree(qh);
  return osOK;
}

osStatus_t WasmMessageQueueGet(WasmMessageQueueType* qh, void* msg_ptr, uint8_t* msg_prio, uint32_t timeout)
{
  osStatus_t ercd = osOK;
  WasmMessageQueueEntryType* entry = NULL;

  WasmThreadSyncLock();
  if (qh->magicno != WASM_MESSAGE_QUEUE_HEAD_MAGICNO) {
    WasmThreadSyncUnlock();
    CMSIS_IMPL_ERROR("ERROR:%s %s() %d invalid magicno=%d\n", __FILE__, __FUNCTION__, __LINE__, qh->magicno);
    return osErrorParameter;
  }
  entry = (WasmMessageQueueEntryType*)WasmQueueHeadRemoveFirst(&qh->used);
  if (entry == NULL) {
    if (timeout != 0) {
      entry = (WasmMessageQueueEntryType*)WasmThreadSyncWait(&qh->getter_waiting, timeout, NULL);
    }
  }
  if (entry != NULL) {
    memcpy(msg_ptr, entry->data, qh->entry_size);
    if (!WasmThreadSyncWakeupFirstEntry(&qh->putter_waiting, entry, osOK)) {
      WasmQueueHeadAddTail(&qh->free, &entry->queue);
    } else {
      /* nothing to do */
    }
  } else {
    ercd = osErrorResource;
  }
  WasmThreadSyncUnlock();
  return ercd;
}
bool_t WasmMessageQueueIsValid(WasmMessageQueueType* qh)
{
  return (qh->magicno == WASM_MESSAGE_QUEUE_HEAD_MAGICNO);
}

osStatus_t WasmMessageQueuePut(WasmMessageQueueType* qh, const void* msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
  osStatus_t ercd = osOK;
  WasmMessageQueueEntryType* entry = NULL;

  WasmThreadSyncLock();
  if (qh->magicno != WASM_MESSAGE_QUEUE_HEAD_MAGICNO) {
    WasmThreadSyncUnlock();
    CMSIS_IMPL_ERROR("ERROR:%s %s() %d invalid magicno=%d\n", __FILE__, __FUNCTION__, __LINE__, qh->magicno);
    return osErrorParameter;
  }
  entry = (WasmMessageQueueEntryType*)WasmQueueHeadRemoveFirst(&qh->free);
  if (entry == NULL) {
    if (timeout != 0) {
      entry = (WasmMessageQueueEntryType*)WasmThreadSyncWait(&qh->putter_waiting, timeout, NULL);
    }
  }
  if (entry != NULL) {
    memcpy(entry->data, msg_ptr, qh->entry_size);
    if (!WasmThreadSyncWakeupFirstEntry(&qh->getter_waiting, entry, osOK)) {
      (void)WasmQueueHeadAddTail(&qh->used, &entry->queue);
    } else {
      /* nothing to do */
    }
  } else {
    ercd = osErrorResource;
  }
  WasmThreadSyncUnlock();
  return ercd;
}
