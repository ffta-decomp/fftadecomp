#include "interfaces.h"
u32 IsEffectAllowedByStatusExemptions(void *actor, void *target, s32 effect_id)
    __asm__("CoreRegion_0012F2CC");

u32 IsEffectAllowedByStatusExemptions(void *actor, void *target, s32 effect_id)
{
    if ((u8)UnitHasSaveGatedStatusPair(target) != 0 &&
        (u8)PassesActorTargetStatusPolicy(actor, target) != 0) {
        switch ((u8)ReadEffectCategory((u8)effect_id)) {
        case 0:
        case 6:
        case 7:
        case 8:
            return 0;
        }
        /* These exclusions use the original full signed ID, not its low byte. */
        switch (effect_id) {
        case 39:
        case 68:
        case 74:
            return 0;
        }
    }
    return 1;
}
