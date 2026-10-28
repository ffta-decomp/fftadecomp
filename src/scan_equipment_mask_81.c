typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Only the five equipment halfwords at +0x2a are modeled. */
typedef struct UnitEquipmentView {
    u8 unknown_00[0x2a];
    u16 equipment[5];
} UnitEquipmentView;

extern u32 InspectEquipmentForScan(UnitEquipmentView *unit, u16 item,
                                   u8 slot, u8 mode);
extern void ReplaceEquipmentSlotForScan(UnitEquipmentView *unit, u16 item,
                                        u8 slot);

/* Find slots whose inspection result contains both bits 7 and 0. Clearing a
 * qualifying slot restarts the scan at slot 1 after the loop increment. */
u8 ScanEquipmentMask81(UnitEquipmentView *unit, u8 clear)
{
    int found = 0;
    int slot;

    for (slot = 0; slot < 5; slot++) {
        u16 item = unit->equipment[slot];
        if (item == 0)
            continue;
        if ((InspectEquipmentForScan(unit, item, (u8)slot, 1) & 0x81) != 0x81)
            continue;
        if (clear) {
            ReplaceEquipmentSlotForScan(unit, 0, (u8)slot);
            slot = 0;
        }
        found = 1;
    }
    return found;
}
