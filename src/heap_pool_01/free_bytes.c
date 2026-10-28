#include "pool_abi.h"

void Free_08007170(void *storage, void *allocation)
{
    /* No null/sentinel guard exists in retail. */
    CoalesceReleasedPoolBlock_08006FCC((u8 *)storage,
                                      (u8 *)((u32)allocation - 12U));
}
