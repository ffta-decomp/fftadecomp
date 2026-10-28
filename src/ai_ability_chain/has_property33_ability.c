/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

#define RETAIL_THUMB_ALIAS(symbol, address) \
    __asm__(".global " #symbol "\n.thumb_set " #symbol ", " address "\n")

RETAIL_THUMB_ALIAS(AbilityUnitHasBit12, "0x080c8299");
RETAIL_THUMB_ALIAS(SelectUnitAbilityEntries, "0x080cce61");
RETAIL_THUMB_ALIAS(AbilityIndexIsAvailable, "0x080cd561");

extern u32 AbilityUnitHasBit12(const u8 *unit);
extern const u8 *SelectUnitAbilityEntries(const u8 *unit, u8 slot,
                                           u8 *first_index, u8 *last_index);
extern u32 AbilityIndexIsAvailable(const u8 *unit, u8 index);

u32 CoreFrontier_001341EC(const u8 *unit);


u32 HasAvailableProperty33Ability(const u8 *unit)
{
    u8 first_index;
    u8 last_index;
    u32 selection = 0;
    s32 slot;
    const u8 *entries;
    s32 index;

    if ((u8)AbilityUnitHasBit12(unit) != 0)
        return 0;

    for (slot = 0; slot <= 2; ++slot) {
        entries = SelectUnitAbilityEntries(unit, (u8)(slot + 1),
                                            &first_index, &last_index);
        switch (slot) {
        case 0:
            selection = unit[53];
            break;
        case 1:
            selection = unit[54];
            break;
        case 2:
            selection = unit[55];
            break;
        }
        if (selection == 0)
            continue;

        {
            const u8 *entry = entries + 8 * first_index;
            index = first_index;
            while (index <= last_index) {
                u8 kind = entry[6];

                if ((kind == 1 || kind == 4) && selection != 1 &&
                    (u8)AbilityIndexIsAvailable(unit, (u8)index) != 0 &&
                    *(const u16 *)(entry + 4) == 33)
                    return 1;
                ++index;
                entry += 8;
            }
        }
    }
    return 0;
}
