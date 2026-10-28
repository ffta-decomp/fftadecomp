#include "interfaces.h"

/* Suppress the existing complete equipment effect before entering its frame. */
void EffectCallback_00133244(EffectContext *context)
{
    if (!(context->flags & 0x10))
        ApplyEquipmentSelectionEffect(context);
}
