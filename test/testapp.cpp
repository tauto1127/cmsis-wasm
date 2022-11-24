#include "cmsis_os.h"
#include <iostream>

int main(int argc, char* argv[])
{
    uint32_t tick;
    tick = osKernelGetTickCount();
    std::cout << "tickCount = " << tick << std::endl;
}