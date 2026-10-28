#include "interfaces.h"

/* The flag suppresses both effects; unit pointers are reloaded after CE1B0. */
void EffectCallback_00131F44(EffectContext *context)
{
    if (!(context->flags & 0x10)) {
        SetUnitFlagEA08(context->primary_unit,1);
        SetUnitFieldE6(context->primary_unit,context->effect_unit->field104);
    }
}
