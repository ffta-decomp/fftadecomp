typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 fields_before_equipment[0x2a];
    u16 equipment[5];
} EquipmentView;

typedef struct {
    u8 count;
    u8 unknown;
    u8 job_ability_pairs[9][2];
} ItemAbilitySet;

typedef struct {
    u8 fields_before_ability_state[0x40];
    u8 states[256];
} UnitAbilityStateView;

typedef struct {
    u8 fields_before_requirement[7];
    u8 requirement;
} AbilityListEntry;

extern const ItemAbilitySet gItemAbilitySets[];
extern void (*const gCopyRecordMemory)(void *, const void *, u32);
extern u32 GetItemProperty(u16 item_id, u8 property);
extern const AbilityListEntry *GetAbilityListEntry(u8 list, u8 index);
extern u8 EquipmentProvidesAbility(const u8 *unit, u8 ability);
extern u8 CheckEquipmentSet(EquipmentView *unit, const u16 *equipment,
                            s8 changed_slot, u8 previous_flags);

/* Evaluate a trial item in one of five equipment slots. The existing item is
 * removed only while testing whether other equipment still grants its
 * unlearned abilities; the original slot value is restored before return.
 * The observed return bits 2, 4, and 8 refer to three selected ability slots.
 */
u32 InspectEquipment(EquipmentView *unit, u16 replacement_item, u8 slot, u8 mode)
{
    u16 equipment[5];
    u8 result_flags = 0;
    u16 current_item;

    gCopyRecordMemory(equipment, unit->equipment, sizeof(equipment));
    current_item = equipment[slot];
    if (current_item == 0) {
        equipment[slot] = replacement_item;
    } else {
        const ItemAbilitySet *ability_set = &gItemAbilitySets[GetItemProperty(current_item, 18)];
        u8 *selected = (u8 *)unit + 0x34;
        u16 previous = unit->equipment[slot];
        unit->equipment[slot] = 0;
        if (previous != replacement_item) {
            int index;
            for (index = 0; index < ability_set->count; ++index) {
                if (ability_set->job_ability_pairs[index][0] &&
                    ability_set->job_ability_pairs[index][0] == ((u8 *)unit)[7]) {
                    u8 ability = ability_set->job_ability_pairs[index][1];
                    if ((((UnitAbilityStateView *)unit)->states[ability] & 0x7f) <
                            GetAbilityListEntry(((u8 *)unit)[6], ability)->requirement &&
                        !EquipmentProvidesAbility((u8 *)unit, ability)) {
                        if (selected[8] == ability) result_flags |= 8;
                        else if (selected[7] == ability) result_flags |= 4;
                        else if (selected[6] == ability) result_flags |= 2;
                    }
                }
            }
        }
        unit->equipment[slot] = previous;
        equipment[slot] = replacement_item;
    }
    result_flags |= CheckEquipmentSet(unit, equipment,
                                      mode ? (s8)slot : -1, result_flags);
    return result_flags;
}
