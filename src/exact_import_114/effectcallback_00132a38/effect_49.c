#include "interfaces.h"

typedef struct {
    u8 reserved_00[42];
    u16 equipment[0];
} AffectedEquipmentTail;

void EffectCallback_00132A38(volatile ApplicationContext *context)
{
    s32 slot;
    u16 item;
    void *affected;
    if (context->flags & 16) return;
    slot = (s8)RetailCall_081329ec(context->affected);
    item = 0;
    if (slot >= 0) {
        affected = context->affected;
        item = ((AffectedEquipmentTail *)affected)->equipment[slot];
        ReplaceEquipmentSlotForScan(affected, 0, (u8)slot);
        EquipmentScanMask81(context->affected, 1);
        if ((u8)EffectApplicationCall_08131BB8(context->affected))
            IT03_RemoveItem(item, 1);
    }
    ApplicationHalf(context, 24) = item;
    UnitModelCall_CA2E8(context->affected);
}
