#include "cmsis_wasm_queue.h"

void WasmQueueHeadAddTail(WasmQueueHeadType* headp, CMSIS_IMPL_QUEUE* entry)
{
  cmsis_impl_queue_initialize(entry);
  if (headp->entries == NULL) {
    headp->entries = entry;
  } else {
    //add last
    cmsis_impl_queue_insert_prev(headp->entries, entry);
  }
  headp->count++;
  return;
}
void WasmQueueHeadRemoveEntry(WasmQueueHeadType* headp, CMSIS_IMPL_QUEUE* entry)
{
  if (headp->entries != NULL) {
    CMSIS_IMPL_QUEUE* next = entry->p_next;
    cmsis_impl_queue_delete(entry);
    headp->count--;
    if (headp->count == 0) {
      headp->entries = NULL;
    } else if (headp->entries == entry) {
      headp->entries = next;
    }
  }
  return;
}
CMSIS_IMPL_QUEUE* WasmQueueHeadRemoveFirst(WasmQueueHeadType* headp)
{
  CMSIS_IMPL_QUEUE* first = headp->entries;
  if (first != NULL) {
    WasmQueueHeadRemoveEntry(headp, first);
  }
  return first;
}
