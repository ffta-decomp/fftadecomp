#include "interfaces.h"

/* The fixed result flag's downstream meaning is not established. */
void EffectCallback_00132550(EffectContext *context)
{
    context->flags |= 0x20;
}
