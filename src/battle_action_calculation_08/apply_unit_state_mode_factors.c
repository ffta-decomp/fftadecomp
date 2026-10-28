/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
struct UnitStateView;
extern u8 UnitStateEBHasBit0(const struct UnitStateView *unit);
extern u8 UnitStateEBHasBit1(const struct UnitStateView *unit);
extern u8 UnitStateE8HasBit6(const struct UnitStateView *unit);
extern u8 UnitStateE9HasBit0(const struct UnitStateView *unit);
extern u8 UnitStateE9HasBit5(const struct UnitStateView *unit);
extern u8 UnitStateEDBit1(const struct UnitStateView *unit);
extern u8 UnitStateEDBit2(const struct UnitStateView *unit);
extern u8 UnitStateECBit7(const struct UnitStateView *unit);
extern u8 UnitStateEDBit0(const struct UnitStateView *unit);
__asm__(".global UnitStateE9HasBit5\n.thumb_set UnitStateE9HasBit5, 0x80cd9d5");
__asm__(".global UnitStateEDBit1\n.thumb_set UnitStateEDBit1, 0x80cdc75");
__asm__(".global UnitStateEDBit2\n.thumb_set UnitStateEDBit2, 0x80cdc8d");
__asm__(".global UnitStateECBit7\n.thumb_set UnitStateECBit7, 0x80cdc45");
__asm__(".global UnitStateEDBit0\n.thumb_set UnitStateEDBit0, 0x80cdc5d");


/* Ordered state multipliers; each low-word product is arithmetically shifted. */
s32 ApplyUnitStateModeFactors(const struct UnitStateView *unit, s32 value, u8 mode)
{
    if (UnitStateEBHasBit0(unit) && mode == 1)
        value = (s32)((u32)value * 358U) >> 8;
    if (UnitStateEBHasBit1(unit) && mode == 0)
        value = (s32)((u32)value * 358U) >> 8;
    if (UnitStateE8HasBit6(unit))
        value = (s32)((u32)value * 460U) >> 8;
    if (UnitStateE9HasBit0(unit))
        value = (s32)((u32)value * 25U) >> 8;
    if (UnitStateE9HasBit5(unit))
        value = (s32)((u32)value * 358U) >> 8;
    if (UnitStateEDBit1(unit) && mode == 1)
        value = (s32)((u32)value * 358U) >> 8;
    if (UnitStateEDBit2(unit) && mode == 1)
        value = (s32)((u32)value * 179U) >> 8;
    if (UnitStateECBit7(unit) && mode == 0)
        value = (s32)((u32)value * 358U) >> 8;
    if (UnitStateEDBit0(unit) && mode == 0)
        value = (s32)((u32)value * 179U) >> 8;
    return value;
}
