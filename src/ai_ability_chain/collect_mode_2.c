#include "retail_calls.h"

u32 CollectAbilityIdsForMode2(u16 *output, const u8 *unit)
{
    return AiCollectAvailableAbilityIds(output, unit, 2);
}
