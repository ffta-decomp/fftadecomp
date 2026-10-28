#include "interfaces.h"

u32 CollectAvailableAbilityIds(u16 *output, AbilityUnit *unit, u8 mode)
{
    u8 first;
    u8 last;
    int list_index;
    int ordinal;
    u32 count = 0;
    u32 list_mode = 0;
    AbilityListRecord *list;
    AbilityListRecord *record;
    u16 *destination;

    if ((u8)UnitAbilityCollectionBlocked(unit) != 0)
        return 0;
    for (list_index = 0; list_index <= 2; ++list_index) {
        list = ReadUnitAbilityList(unit, (u8)(list_index + 1), &first, &last);
        switch (list_index) {
        case 0: list_mode = unit->list_modes[0]; break;
        case 1: list_mode = unit->list_modes[1]; break;
        case 2: list_mode = unit->list_modes[2]; break;
        }
        if (list_mode != 0) {
            record = list + first;
            ordinal = first;
            if (ordinal <= last) {
                /* GBA addresses use the halfword-count byte offset before the base. */
                destination = (u16 *)(count * sizeof(*output) + (u32)output);
                do {
                    if (record->kind == 1 || record->kind == 4) {
                        if (list_mode == 1) {
                            if ((u8)UnitUsesInventoryAbilityMapping(unit) == 1) {
                                if ((u8)HasAbilityInventoryItem((u16)ReadAbilityInventoryItem((u8)ordinal)) == 0)
                                    goto next_record;
                            }
                        } else {
                            if ((u8)IsUnitAbilityListEntryAvailable(unit, (u8)ordinal) == 0)
                                goto next_record;
                        }
                        if ((u8)AbilityOutputContains(record->ability, output, count) != 0)
                            goto next_record;
                        if ((u8)CanUseAbilityInCollectionMode(unit, record->ability, (s8)mode) != 0) {
                            *destination = record->ability;
                            ++destination;
                            ++count;
                        }
                    }
                next_record:
                    ++ordinal;
                    ++record;
                } while (ordinal <= last);
            }
        }
    }
    return count;
}
