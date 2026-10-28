#include "interfaces.h"

void ApplyRandomTwentyWayEvent(volatile ApplicationContext *context)
{
    s32 choice;
    if (context->flags & 16) return;
    choice = IT03_SignedRemainder((s16)IP03_RandomWord(), 20);
    EffectApplicationCall_0802DA00((u8)choice);
}
