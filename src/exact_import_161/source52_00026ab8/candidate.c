#include "interfaces.h"

u8 HasSelectedAvailableAbilityWithFlag8(void) __asm__("Source52_00026AB8");
u8 HasSelectedAvailableAbilityWithFlag8(void)
{
    u8 selected = 0;
    s32 slot;
    u8 first_index, last_index;

    for (slot = 0; slot <= 2; ++slot) {
        switch (slot) {
        case 0: selected = gActiveAbilitySelection->unit[53]; break;
        case 1: selected = gActiveAbilitySelection->unit[54]; break;
        case 2: selected = gActiveAbilitySelection->unit[55]; break;
        }
        if (selected != 0) {
            const u8 *list = SelectUnitAbilityList(gActiveAbilitySelection->unit,
                                                  slot + 1, &first_index, &last_index);
            s32 index = first_index;
            if (index <= last_index) {
                const struct AbilityEntryView *entry;
                u32 record_offset = index * 8 + 4;
                /* The pinned Thumb compiler reverses this commutative sum.
                 * Preserve the observed offset/base allocation boundary only. */
                __asm__("add %0, %1, %2"
                        : "=l"(entry)
                        : "l"(record_offset), "l"(list)
                        : "cc");
                do {
                    if ((entry->availability_kind == 1 || entry->availability_kind == 4)
                        && IsAbilityAvailable(gActiveAbilitySelection->unit, index)
                        && GetAbilityProperty(entry->ability_id, 19))
                        return 1;
                    ++entry;
                    ++index;
                } while (index <= last_index);
            }
        }
    }
    return 0;
}
