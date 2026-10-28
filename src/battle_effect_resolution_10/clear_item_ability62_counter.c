/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ItemRecord { u8 prefix[26]; u8 abilities[3]; u8 tail[3]; };
extern const struct ItemRecord gItemRecords[];
extern u32 PropertyPredicate_000CCD50(u16 id, u32 selector);
extern void SetUnitStateEABit4(void *unit, u8 value);
extern void WriteUnitCounterD9(void *unit, u8 value);

asm(".global gItemRecords\n.set gItemRecords,0x0851d180\n.global PropertyPredicate_000CCD50\n.thumb_set PropertyPredicate_000CCD50,0x080ccd51");
void ClearUnitCounterForItemAbility62(u16 item_id, u16 condition_id, void *unit)
{
    int ability_slot;
    const struct ItemRecord *item;
    if (!item_id)
        return;
    if (condition_id && !PropertyPredicate_000CCD50(condition_id, 3))
        return;
    item = &gItemRecords[item_id];
    for (ability_slot = 0; ability_slot <= 2; ability_slot++) {
        if (item->abilities[ability_slot] == 62) {
            SetUnitStateEABit4(unit, 0);
            WriteUnitCounterD9(unit, 0);
            break;
        }
    }
}
