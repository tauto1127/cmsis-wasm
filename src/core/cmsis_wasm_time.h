#ifndef _CMSIS_WASM_TIME_H_
#define _CMSIS_WASM_TIME_H_

#include "cmsis_wasm_common.h"

extern uint32_t PosixOsTimeGetTickCount(void);
extern osStatus_t PosixOsTimerInit(void);

#endif /* _CMSIS_WASM_TIME_H_ */
