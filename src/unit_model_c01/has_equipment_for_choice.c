/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitEquipmentView { u8 unknown[42]; u16 equipment[5]; };
extern u32 GetItemProperty(u16,u8);

u32 UnitHasEquipmentForChoice(const struct UnitEquipmentView *unit, u8 choice)
{
    int slot;
    for (slot=0;slot<5;slot++) {
        u16 item_id = unit->equipment[slot];
        if (item_id != 0) {
            u16 item_class = GetItemProperty(item_id,3);
            switch (choice) {
            case 2:
                if (item_class == 15) return 1;
                break;
            case 3:
                if ((u16)(item_class-13) <= 1) return 1;
                break;
            }
        }
    }
    return 0;
}
