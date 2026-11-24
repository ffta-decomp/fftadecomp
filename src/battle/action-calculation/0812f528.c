/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
struct UnitStateView;
extern u8 UnitStateE8HasBit7(const struct UnitStateView *unit);
__asm__(".global UnitStateE8HasBit7\n.thumb_set UnitStateE8HasBit7, 0x80cd945");
extern u8 UnitStateE9HasBit0(const struct UnitStateView *unit);
__asm__(".global UnitStateE9HasBit0\n.thumb_set UnitStateE9HasBit0, 0x80cd95d");
extern u8 UnitStateE9HasBit6(const struct UnitStateView *unit);
__asm__(".global UnitStateE9HasBit6\n.thumb_set UnitStateE9HasBit6, 0x80cd9ed");
extern u8 UnitStateECBit3(const struct UnitStateView *unit);
__asm__(".global UnitStateECBit3\n.thumb_set UnitStateECBit3, 0x80cdbe5");
extern u8 UnitStateECBit4(const struct UnitStateView *unit);
__asm__(".global UnitStateECBit4\n.thumb_set UnitStateECBit4, 0x80cdbfd");
extern u8 UnitStateECBit5(const struct UnitStateView *unit);
__asm__(".global UnitStateECBit5\n.thumb_set UnitStateECBit5, 0x80cdc15");
extern u8 UnitStateECBit6(const struct UnitStateView *unit);
__asm__(".global UnitStateECBit6\n.thumb_set UnitStateECBit6, 0x80cdc2d");


/* Narrow only the incoming value; successive state factors retain full32. */
s32 ApplyUnitStateValueFactors(const struct UnitStateView *unit, u8 mode, s16 initial_value)
{
    s32 value = initial_value;
    if (UnitStateE8HasBit7(unit) && mode == 0)
        value = (s32)((u32)value * 307U) >> 8;
    if (UnitStateE9HasBit0(unit))
        value = (s32)((u32)value * 25U) >> 8;
    if (UnitStateE9HasBit6(unit) && mode == 0)
        value = (s32)((u32)value * 384U) >> 8;
    if (UnitStateECBit3(unit) && mode == 0)
        value = (s32)((u32)value * 281U) >> 8;
    if (UnitStateECBit4(unit) && mode == 0)
        value = (s32)((u32)value * 230U) >> 8;
    if (UnitStateECBit5(unit) && mode == 1)
        value = (s32)((u32)value * 281U) >> 8;
    if (UnitStateECBit6(unit) && mode == 1)
        value = (s32)((u32)value * 230U) >> 8;
    return value;
}
