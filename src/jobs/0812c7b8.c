typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 ReadPolicyProperty(const u8 *unit, u8 selector);
extern u8 TestUnitE90(const void *unit);
extern u32 SumEquipmentProperty(const u8 *unit, u32 selector);
__asm__(".global ReadPolicyProperty\n.thumb_set ReadPolicyProperty, 0x080c92f1");
__asm__(".global TestUnitE90\n.thumb_set TestUnitE90, 0x080cd95d");
__asm__(".global SumEquipmentProperty\n.thumb_set SumEquipmentProperty, 0x080ca4f1");

/* Keep full-word addition before signed clamping; no narrowing. */
u32 ClampUnitProperty32WithEquipment15(const u8 *unit) __asm__("CoreRegion_0012C7B8");
u32 ClampUnitProperty32WithEquipment15(const u8 *unit)
{
    u32 value = ReadPolicyProperty(unit, 32);
    if ((u8)TestUnitE90(unit) == 0)
        value += SumEquipmentProperty(unit, 15);
    if ((s32)value < 0)
        return 0;
    if ((s32)value > 100)
        return 100;
    return value;
}
