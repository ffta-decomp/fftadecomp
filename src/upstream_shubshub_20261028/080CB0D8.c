/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CB0D8.c
 * Original SHA-256: d9f4111127d9e39f7ad696236bfe65396cadc2eb017b67ac9216b956b8077e02
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 selected[3];
    u8 special;
    u8 unknown_0A[2];
    u8 progress[0];
} AbilityState;

typedef struct {
    u8 unknown_00[6];
    u8 job;
    u8 race;
    u8 unknown_08[0x22];
    u16 equipment[5];
    AbilityState abilities;
} Unit;

typedef u8 ItemAbility[2];

typedef struct {
    u8 count;
    u8 unknown_01;
    ItemAbility entries[9];
} ItemAbilities;

typedef struct {
    u8 unknown_00[7];
    u8 required;
} AbilityInfo;

extern const ItemAbilities g_table_08520080[];
extern u32 func_080CA7A4(u16 item, u32 field);
extern AbilityInfo *func_080CD480(u8 job, u8 ability);
extern u8 func_080CD1FC(Unit *unit, u8 ability);
extern void func_080CD620(Unit *unit, u8 ability);
extern void func_080CCF44(Unit *unit, u16 item);

void func_080CB0D8(Unit *unit, u16 item, u8 slot)
{
    u16 old_item = unit->equipment[slot];

    if (old_item) {
        const ItemAbilities *item_abilities;
        AbilityState *abilities;
        s32 i;

        if (item == old_item)
            return;
        item_abilities = &g_table_08520080[func_080CA7A4(old_item, 0x12)];
        abilities = &unit->abilities;
        unit->equipment[slot] = 0;
        for (i = 0; i < item_abilities->count; i++) {
            u8 race = item_abilities->entries[i][0];

            if (race) {
                if (race == unit->race) {
                    u8 ability = item_abilities->entries[i][1];
                    u8 progress = unit->abilities.progress[ability] & 0x7F;

                    if (progress < func_080CD480(unit->job, ability)->required) {
                        if (!func_080CD1FC(unit, ability)) {
                            if (abilities->selected[2] == ability)
                                abilities->selected[2] = 0;
                            else if (abilities->selected[1] == ability)
                                abilities->selected[1] = 0;
                            else if (abilities->selected[0] == ability)
                                abilities->selected[0] = 0;
                            abilities->progress[ability] &= 0x7F;
                            func_080CD620(unit, ability);
                        }
                    }
                } else if (race == 0xFF) {
                    if (func_080CA7A4(old_item, 3) == 0x1B)
                        abilities->special = 0;
                }
            }
        }
    }
    unit->equipment[slot] = item;
    func_080CCF44(unit, item);
}
