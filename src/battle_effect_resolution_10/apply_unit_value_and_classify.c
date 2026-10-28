#include "apply_unit_value_and_classify_exact_types.h"

struct ValueUnit {
    u8 unknown_00[24];
    u16 current_value;
};

static inline u32 ClassifyUnitValue(struct ValueUnit *unit)
{
    u32 current;
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
    current = ReadUnitField(unit, 19);
    if (current > (ReadUnitField(unit, 20) >> 2))
        goto class_three;
class_two:
    classification = 2;
    goto classified;
class_three:
    classification = 3;
classified:
    return classification;
}

u32 ApplyBattleUnitValueAndClassify(struct ValueUnit *unit, u16 delta);
u32 ApplyBattleUnitValueAndClassify(struct ValueUnit *unit, u16 delta)
{
    u32 previous_class;
    u32 current_class;
    u16 remaining;
    s32 signed_remaining;
    s32 current_signed;
    s32 delta_signed;

    previous_class = ClassifyUnitValue(unit);
    current_signed = (s16)ReadUnitField(unit, 19);
    delta_signed = (s16)delta;
    remaining = current_signed - delta_signed;
    if ((s16)remaining < 0)
        remaining = 0;
    signed_remaining = (s16)remaining;
    if ((u32)signed_remaining > ReadUnitField(unit, 20))
        remaining = ReadUnitField(unit, 20);
    unit->current_value = remaining;
    current_class = ClassifyUnitValue(unit);
    if (current_class == previous_class)
        return 0;
    return current_class;
}
