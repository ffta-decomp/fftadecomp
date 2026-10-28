#include "interfaces.h"
void RemoveEquipmentFromAffectedSlot67(volatile ApplicationContext *context)
{
    u16 equipment[2];
    s32 count, next_slot;
    /* Original r4 changes from outer slot to inner countdown; r5 is the cursor. */
    register s32 slot asm("r4");
    u32 replacement_slot;
    u16 item;
    u16 *cursor;
    if (context->flags & 16) return;
    count = RetailCall_0812f0cc(context->affected, equipment);
    if (count <= 0) return;
    slot = 0;
    do {
        item = (u16)IP03_GetUnitName(context->affected, (u8)(slot + 29));
        next_slot = slot + 1;
        if (item != 0 && count > 0) {
            cursor = equipment;
            replacement_slot = (u32)slot << 24;
            slot = count;
            do {
                if (*cursor == item) {
                    ReplaceEquipmentSlotForScan(context->affected, 0, replacement_slot >> 24);
                    EquipmentScanMask81(context->affected, 1);
                }
                ++cursor;
                --slot;
            } while (slot != 0);
        }
        slot = next_slot;
    } while (slot <= 4);
    UnitModelCall_CA2E8(context->affected);
}
