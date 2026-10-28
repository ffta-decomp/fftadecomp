/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ItemRecord { u8 prefix[26]; u8 abilities[3]; u8 tail[3]; };
extern const struct ItemRecord gItemRecords[];
extern u32 ReadUnitField(const void *unit, u8 selector);

/* Original fixed item-table base, declaration only. */
asm(".global gItemRecords\n.set gItemRecords,0x0851d180");
u8 CountEquipmentWithAbility60(const void *unit)
{
    int matches = 0;
    int equipment_slot;
    for (equipment_slot = 0; equipment_slot <= 4; equipment_slot++) {
        u16 item_id = ReadUnitField(unit, equipment_slot + 29);
        if (item_id) {
            int ability_slot;
            const struct ItemRecord *item = &gItemRecords[item_id];
            for (ability_slot = 0; ability_slot <= 2; ability_slot++) {
                if (item->abilities[ability_slot] == 60) {
                    matches++;
                    break;
                }
            }
        }
    }
    return matches;
}
