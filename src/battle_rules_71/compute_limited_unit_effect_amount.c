/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 UnitStateECBit1(const u8 *unit);
extern s32 ComputeBaseUnitEffect(const u8 *unit, const u8 *target, u16 ability_id, u16 item_id, u16 extra, u8 mode, u8 flags);
extern u32 ReadUnitField(const u8 *unit, u8 selector);
extern u32 NextRandom15(void);
__asm__(".global UnitStateECBit1\n.thumb_set UnitStateECBit1, 0x080cda4d");
__asm__(".global ComputeBaseUnitEffect\n.thumb_set ComputeBaseUnitEffect, 0x0812fe39");
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x080c7ea5");
__asm__(".global NextRandom15\n.thumb_set NextRandom15, 0x08002805");
__asm__(".global __udivsi3\n.thumb_set __udivsi3, 0x08142ab1");
__asm__(".global __modsi3\n.thumb_set __modsi3, 0x08142951");


/* ComputeBaseUnitEffect clamps its result to -999..999. */
#define EFFECT_MAGNITUDE(value) ((value) < 0 ? -(value) : (value))

s32 ComputeLimitedUnitEffectAmount(const u8 *unit, const u8 *target, u16 unused_ability_id, u16 item_id, u8 flags);
s32 ComputeLimitedUnitEffectAmount(const u8 *unit, const u8 *target, u16 unused_ability_id, u16 item_id, u8 flags)
{
    s32 base_amount;
    s32 amount;
    u32 variance_mask;
    if (UnitStateECBit1(target))
        return 0;
    variance_mask = 2;
    base_amount = ComputeBaseUnitEffect(unit, target, 0, item_id, 0, variance_mask, 0);
    amount = ReadUnitField(unit, 6) / 10;
    if (amount <= 0)
        amount = 1;
    if (base_amount == 0)
        amount = 0;
    if (base_amount < 0)
        amount = -amount;
    if (!(flags & variance_mask)) {
        if (base_amount > 0)
            amount += (s16)((s16)NextRandom15() % 11);
        else if (base_amount < 0)
            amount -= (s16)((s16)NextRandom15() % 11);
    }
    if (amount < -EFFECT_MAGNITUDE(base_amount))
        amount = -EFFECT_MAGNITUDE(base_amount);
    if (amount > EFFECT_MAGNITUDE(base_amount))
        amount = EFFECT_MAGNITUDE(base_amount);
    return amount;
}
