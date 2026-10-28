/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct AbilityValueEntry {
    u8 prefix[4];
    u16 value;
    u8 category;
    u8 requirement;
};
extern u32 ReadUnitField(const u8 *unit, u8 selector);
extern const struct AbilityValueEntry *GetAbilityListEntry(u8 list, u8 index);


/* The unit's current entry limit is reloaded after each helper pair. */
u16 FindUnitAbilityValueIndex(const u8 *unit, u16 value)
{
    s32 index = 1;

    while (index < unit[52]) {
        u8 list = (u8)ReadUnitField(unit, 3);
        const struct AbilityValueEntry *entry = GetAbilityListEntry(list, (u8)index);
        if (entry->value == value)
            return index;
        ++index;
    }
    return 0xffff;
}
