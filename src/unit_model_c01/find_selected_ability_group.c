/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct AbilityRecord { u16 id; u8 kind; u8 tail[5]; };
struct AbilityTable { u32 header; struct AbilityRecord records[0]; };
struct UnitAbilitySlots { u8 prefix[53]; u8 first; u8 second; u8 third; };
extern const struct AbilityTable *GetUnitAbilityRange(const struct UnitAbilitySlots *unit, u8 group, u8 *first, u8 *last);

asm(".global GetUnitAbilityRange\n.thumb_set GetUnitAbilityRange,0x080cce61");
u32 FindSelectedAbilityGroupValue(const struct UnitAbilitySlots *unit, u16 ability_id)
{
    u8 first;
    u8 last;
    u32 selected = 0;
    int group;
    for (group = 0; group <= 2; group++) {
        const struct AbilityTable *table = GetUnitAbilityRange(unit, group + 1, &first, &last);
        int index;
        switch (group) {
        case 0: selected = unit->first; break;
        case 1: selected = unit->second; break;
        case 2: selected = unit->third; break;
        }
        if (selected) {
            for (index = first; index <= last; index++) {
                const struct AbilityRecord *record = &table->records[index];
                if ((record->kind == 1 || record->kind == 4) && record->id == ability_id)
                    return selected;
            }
        }
    }
    return 0;
}
