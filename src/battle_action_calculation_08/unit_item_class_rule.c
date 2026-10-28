/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetItemProperty(u16 item_id, u8 property);
extern u32 BattleDependency_0012E6A4(const u8 *unit);
asm(".global BattleDependency_0012E6A4\n.thumb_set BattleDependency_0012E6A4, 0x0812e6a5");


u32 UnitItemClassPassesRule(const u8 *unit, u16 item_id, u8 allow_class7)
{
    u32 unit_class = (u16)BattleDependency_0012E6A4(unit);
    if (unit_class == 7 && !allow_class7)
        unit_class = 0;
    if (unit_class != 7 && unit_class != 5) {
        if (unit_class != 6 || GetItemProperty(item_id, 3) - 13u > 1u)
            return 0;
    }
    return 1;
}
