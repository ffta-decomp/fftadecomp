#include "effect_context.h"

/* The status caption is unknown; preserve the specific bit and byte effects. */
void EffectCallback_00133668(EffectContext *context)
{
    if ((context->flags & 0x10) == 0) {
        SetUnitStateEABit2(context->unit, 1);
        /* The helper may change the context: reload unit and the source byte. */
        WriteUnitCounterE6(context->unit, (u8)(context->source_value + 0x36));
    }
}
