/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 GetAbilityProperty(u16 ability_id, u8 selector);
extern s16 ReadUnitBasePower(const u8 *unit, u16 category);
/* The original call also supplies an unused fifth zero word; retain that ABI. */
extern s16 AdjustPowerForUnitAbility(const u8 *unit, s16 power, u16 ability_id, u16 item_id, u32 unused);
extern s32 AdjustPowerForUnitStates(const u8 *unit, u8 category, s16 power);
extern s32 ApplyTargetDefenseAndVariance(s32 power, const u8 *target, u8 suppress_variance);
__asm__(".global GetAbilityProperty\n.thumb_set GetAbilityProperty, 0x080ccd51");
__asm__(".global ReadUnitBasePower\n.thumb_set ReadUnitBasePower, 0x0812f411");
__asm__(".global AdjustPowerForUnitAbility\n.thumb_set AdjustPowerForUnitAbility, 0x0812f48d");
__asm__(".global AdjustPowerForUnitStates\n.thumb_set AdjustPowerForUnitStates, 0x0812f529");
__asm__(".global ApplyTargetDefenseAndVariance\n.thumb_set ApplyTargetDefenseAndVariance, 0x0813010d");

__asm__(".global __divsi3\n.thumb_set __divsi3, 0x081426b9");


s32 ComputeAbilityPowerAgainstUnit(const u8 *unit, const u8 *target, u16 ability_id, u8 mode);
s32 ComputeAbilityPowerAgainstUnit(const u8 *unit, const u8 *target, u16 ability_id, u8 mode)
{
    u32 category;
    s32 power;
    if (ability_id == 251)
        return 25;
    if (ability_id == 252)
        return 50;
    if (ability_id == 253)
        return 150;
    if (ability_id == 0 || GetAbilityProperty(ability_id, 29))
        category = 0;
    else
        category = 1;
    power = ReadUnitBasePower(unit, category);
    power = AdjustPowerForUnitAbility(unit, (s16)power, ability_id, 0, 0);
    {
        s32 state_power = AdjustPowerForUnitStates(unit, category, (s16)power);
        power = ApplyTargetDefenseAndVariance(state_power, target, mode == 2);
    }
    /* The original multiply keeps low32, followed by signed division. */
    power = (s32)(GetAbilityProperty(ability_id, 33) * (u32)power) / 100;
    if (power <= 0)
        power = 1;
    if (power > 999)
        power = 999;
    return power;
}
