#include "interfaces.h"

/* Original default pair-state call; keep every ABI slot and the call itself. */
u8 InvokeDefaultUnitPairState(void *unit) asm("CoreFrontier_00134B38");
u8 InvokeDefaultUnitPairState(void *unit)
{
    return (u8)UpdateUnitPairCounters(unit, 0, 0, 0, 0, 0, 1, 1, 0);
}
