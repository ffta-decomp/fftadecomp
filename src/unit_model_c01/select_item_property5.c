/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetUnitProperty(const u8 *unit, u8 property);
extern u32 GetItemProperty(u16 item_id, u8 property);


u32 SelectUnitItemProperty5(const u8 *unit, u16 item_id)
{
    u32 value;
    if (unit != 0 && (GetUnitProperty(unit, 40) & 4))
        return 4;
    if (item_id != 0)
        value = (u8)GetItemProperty(item_id, 5);
    else
        value = 1;
    return value;
}
