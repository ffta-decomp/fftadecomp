/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 ReadUnitField(const u8 *unit, u8 selector);
extern u32 GetItemProperty(u16 item, u8 selector);


/* The full field is tested before narrowing only the item-property argument. */
u32 HasEquippedItemCategory(const u8 *unit, const u16 *categories, s32 count)
{
    s32 slot = 0;

    do {
        u32 item = ReadUnitField(unit, (u8)(slot + 29));
        if (item != 0) {
            u32 category = GetItemProperty((u16)item, 3);
            s32 index = 0;
            if (index < count) {
                const u16 *cursor = categories;
                do {
                    if (category == *cursor)
                        return 1;
                    ++cursor;
                    ++index;
                } while (index < count);
            }
        }
        ++slot;
    } while (slot <= 4);
    return 0;
}
