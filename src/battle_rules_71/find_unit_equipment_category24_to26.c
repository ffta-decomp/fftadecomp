/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct BattleUnitFieldView;
extern u32 ReadUnitField(const struct BattleUnitFieldView *, u8);
extern u32 GetItemProperty(u16, u8);


/* Category labels remain neutral; the original tests 26, 24, then 25. */
s8 FindUnitEquipmentCategory24To26(const struct BattleUnitFieldView *unit);
s8 FindUnitEquipmentCategory24To26(const struct BattleUnitFieldView *unit)
{
    s32 slot_index;
    for (slot_index = 0; slot_index <= 4; slot_index++) {
        u16 item_id = (u16)ReadUnitField(unit, slot_index + 29);
        if (item_id != 0) {
            u8 category = (u8)GetItemProperty(item_id, 3);
            if (category == 26 || category == 24 || category == 25)
                return (s8)slot_index;
        }
    }
    return -1;
}
