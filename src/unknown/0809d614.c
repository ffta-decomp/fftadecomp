#include "abi/interfaces/0809d614_bindings.h"

route_u32 GetBattleRouteAdjustmentFlag(void *record)
{
    return (RouteByte(record, 41) >> 1) & 1;
}
