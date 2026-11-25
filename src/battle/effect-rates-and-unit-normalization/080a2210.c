#include "battle/effect-rates-and-unit-normalization/interfaces/080a2210_apply_unit_value_and_classify_exact_types.h"
#include "jobs/unit_field_access.h"

struct ValueUnit {
    u8 unknown_00[24];
    u16 current_hp;
};

static inline u32 ClassifyUnitValue(struct ValueUnit *unit)
{
    u32 current_hp;
    u32 classification;
    if ((u8)UnitValueGate(unit) != 0) {
        classification = 1;
        goto classified;
    }
    if ((u8)UnitStateE8Bit6(unit) != 0) {
        if ((u8)UnitStateEDBit4(unit) != 0)
            goto class_two;
        goto class_three;
    }
    current_hp = ReadUnitCurrentHp(unit);
    /* At or below a quarter of max HP takes the low-HP class. */
    if (current_hp > (ReadUnitMaxHp(unit) >> 2))
        goto class_three;
class_two:
    classification = 2;
    goto classified;
class_three:
    classification = 3;
classified:
    return classification;
}

u32 ApplyBattleUnitValueAndClassify(struct ValueUnit *unit, u16 hp_delta);
u32 ApplyBattleUnitValueAndClassify(struct ValueUnit *unit, u16 hp_delta)
{
    u32 previous_class;
    u32 current_class;
    u16 remaining_hp;
    s32 signed_remaining_hp;
    s32 signed_current_hp;
    s32 signed_hp_delta;

    previous_class = ClassifyUnitValue(unit);
    signed_current_hp = (s16)ReadUnitCurrentHp(unit);
    signed_hp_delta = (s16)hp_delta;
    remaining_hp = signed_current_hp - signed_hp_delta;
    if ((s16)remaining_hp < 0)
        remaining_hp = 0;
    signed_remaining_hp = (s16)remaining_hp;
    if ((u32)signed_remaining_hp > ReadUnitMaxHp(unit))
        remaining_hp = ReadUnitMaxHp(unit);
    unit->current_hp = remaining_hp;
    current_class = ClassifyUnitValue(unit);
    if (current_class == previous_class)
        return 0;
    return current_class;
}
