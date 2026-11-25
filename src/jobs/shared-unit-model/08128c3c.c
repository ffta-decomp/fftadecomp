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


#define STAT_REDUCTION_MAX_HP 0
#define STAT_REDUCTION_MAX_MP 1
#define STAT_REDUCTION_WEAPON_ATTACK 2
#define STAT_REDUCTION_WEAPON_DEFENSE 3
#define STAT_REDUCTION_MAGIC_POWER 4
#define STAT_REDUCTION_MAGIC_RESISTANCE 5
#define STAT_REDUCTION_SPEED 6

#define MAX_UNSIGNED_STAT_REDUCTION 99
#define SPEED_REDUCTION_LIMIT 10
#define MIN_REDUCED_SPEED 10

#define UNSIGNED_STAT_REDUCTION_CASE(selector, field, read_base) \
    case selector: \
        amount = DivideUnsigned(read_base(unit), divisor); \
        if (amount == 0) \
            amount = 1; \
        else if (amount > MAX_UNSIGNED_STAT_REDUCTION) \
            amount = MAX_UNSIGNED_STAT_REDUCTION; \
        if (unit->field <= amount) \
            amount = unit->field - 1; \
        unit->field -= amount;

/* Apply one source-selected unit reduction; the return is only its low byte.
 * Quotients wrap to 16 bits before signed zero/upper-limit comparisons. */
u8 ApplyUnitValueReduction(ReductionContext *context, u8 selection)
{
    UnitValues *unit = context->unit;
    s16 amount = 0;
    u8 divisor = UnitReductionDivisors[context->descriptor->divisor_selector];

    switch (selection) {
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_MAX_HP, max_hp, ReadUnitJobBaseHp)
        if (unit->current_hp > unit->max_hp)
            unit->current_hp = unit->max_hp;
        break;
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_MAX_MP, max_mp, ReadUnitJobBaseMp)
        if (unit->current_mp > unit->max_mp)
            unit->current_mp = unit->max_mp;
        break;
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_WEAPON_ATTACK, base_weapon_attack, ReadUnitJobBaseWeaponAttack)
        break;
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_WEAPON_DEFENSE, base_weapon_defense, ReadUnitJobBaseWeaponDefense)
        break;
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_MAGIC_POWER, base_magic_power, ReadUnitJobBaseMagicPower)
        break;
    UNSIGNED_STAT_REDUCTION_CASE(STAT_REDUCTION_MAGIC_RESISTANCE, base_magic_resistance, ReadUnitJobBaseMagicResistance)
        break;
    case STAT_REDUCTION_SPEED:
        amount = DivideSigned(10, divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > SPEED_REDUCTION_LIMIT)
            amount = SPEED_REDUCTION_LIMIT;
        if (unit->base_speed - amount <= MIN_REDUCED_SPEED)
            amount = unit->base_speed - MIN_REDUCED_SPEED;
        unit->base_speed -= amount;
        break;
    }
    return amount;
}

#undef UNSIGNED_STAT_REDUCTION_CASE
