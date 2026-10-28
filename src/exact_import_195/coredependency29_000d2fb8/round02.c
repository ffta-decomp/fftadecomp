#include "interfaces.h"
u32 IsMissionOutcomeRecordId(u16 mission_id) __asm__("CoreDependency29_000D2FB8");
u32 IsMissionOutcomeRecordId(u16 mission_id)
{
    /* The subtraction wraps before the unsigned interval comparison. */
    if ((u16)(mission_id - 0x150) <= 22)
        return 1;
    return 0;
}
