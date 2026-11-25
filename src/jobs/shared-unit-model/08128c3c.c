/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
#include "jobs/unit_property_access.h"
typedef signed short s16;
typedef signed int s32;

typedef struct UnitValues {
    u8 prefix[24];
    u16 current_hp;
    u16 max_hp;
    u16 current_mp;
    u16 max_mp;
    u16 base_weapon_attack;
    u16 base_weapon_defense;
    u16 base_magic_power;
    u16 base_magic_resistance;
    u8 remaining[170];
    s16 base_speed;
} UnitValues;
typedef struct RuleDescriptor {
    u8 prefix[2];
    u8 divisor_selector : 3;
    u8 remaining_bits : 5;
} __attribute__((packed)) RuleDescriptor;
typedef char DescriptorByteSize[sizeof(RuleDescriptor) == 3 ? 1 : -1];
typedef struct ReductionContext {
    u8 prefix[8];
    UnitValues *unit;
    const RuleDescriptor *descriptor;
} ReductionContext;
#define OFFSET(T, M) ((u32)&(((T *)0)->M))
typedef char UnitMaxHpOffset[OFFSET(UnitValues, max_hp) == 26 ? 1 : -1];
typedef char UnitMaxMpOffset[OFFSET(UnitValues, max_mp) == 30 ? 1 : -1];
typedef char UnitMagicResistanceOffset[OFFSET(UnitValues, base_magic_resistance) == 38 ? 1 : -1];
typedef char UnitSpeedOffset[OFFSET(UnitValues, base_speed) == 210 ? 1 : -1];
typedef char ContextUnitOffset[OFFSET(ReductionContext, unit) == 8 ? 1 : -1];
typedef char ContextDescriptorOffset[OFFSET(ReductionContext, descriptor) == 12 ? 1 : -1];
extern const u8 UnitReductionDivisors[8];
extern u32 GetUnitProperty(const void *, u8);
extern u32 DivideUnsigned(u32, u32);
extern s32 DivideSigned(s32, s32);
__asm__(".global UnitReductionDivisors\n.set UnitReductionDivisors, 0x083a8260");
__asm__(".global GetUnitProperty\n.thumb_set GetUnitProperty, 0x080c92f1");
__asm__(".global DivideUnsigned\n.thumb_set DivideUnsigned, 0x08142ab1");
__asm__(".global DivideSigned\n.thumb_set DivideSigned, 0x081426b9");


/* Apply one source-selected unit reduction; the return is only its low byte.
 * Quotients wrap to 16 bits before signed zero/upper-limit comparisons. */
u8 ApplyUnitValueReduction(ReductionContext *context, u8 selection)
{
    UnitValues *unit = context->unit;
    s16 amount = 0;
    u8 divisor = UnitReductionDivisors[context->descriptor->divisor_selector];

    switch (selection) {
    case 0:
        amount = DivideUnsigned(ReadUnitJobBaseHp(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->max_hp <= amount)
            amount = unit->max_hp - 1;
        unit->max_hp -= amount;
        if (unit->current_hp > unit->max_hp)
            unit->current_hp = unit->max_hp;
        break;
    case 1:
        amount = DivideUnsigned(ReadUnitJobBaseMp(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->max_mp <= amount)
            amount = unit->max_mp - 1;
        unit->max_mp -= amount;
        if (unit->current_mp > unit->max_mp)
            unit->current_mp = unit->max_mp;
        break;
    case 2:
        amount = DivideUnsigned(ReadUnitJobBaseWeaponAttack(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->base_weapon_attack <= amount)
            amount = unit->base_weapon_attack - 1;
        unit->base_weapon_attack -= amount;
        break;
    case 3:
        amount = DivideUnsigned(ReadUnitJobBaseWeaponDefense(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->base_weapon_defense <= amount)
            amount = unit->base_weapon_defense - 1;
        unit->base_weapon_defense -= amount;
        break;
    case 4:
        amount = DivideUnsigned(ReadUnitJobBaseMagicPower(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->base_magic_power <= amount)
            amount = unit->base_magic_power - 1;
        unit->base_magic_power -= amount;
        break;
    case 5:
        amount = DivideUnsigned(ReadUnitJobBaseMagicResistance(unit), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->base_magic_resistance <= amount)
            amount = unit->base_magic_resistance - 1;
        unit->base_magic_resistance -= amount;
        break;
    case 6:
        amount = DivideSigned(10, divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 10)
            amount = 10;
        if (unit->base_speed - amount <= 10)
            amount = unit->base_speed - 10;
        unit->base_speed -= amount;
        break;
    }
    return amount;
}
