#include "cmsis_os.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    uint32_t tick;
    tick = osKernelGetTickCount();
    printf("tick = %u\n", tick);
}