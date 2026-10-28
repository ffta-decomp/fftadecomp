/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int UnitField19IsZero(const u8 *unit);
extern u32 HasEquippedItemStateProperty(const u8 *unit, u16 property);
extern void SetUnitStateE8Bit5(u8 *unit, u8 set);
extern void SetUnitStateE8Bit2(u8 *unit, u8 set);
__asm__(".global HasEquippedItemStateProperty\n.thumb_set HasEquippedItemStateProperty, 0x0812ed05");


/* Each equipment predicate runs after any preceding state-bit update. */
void ApplyEquippedItemStateBits(u8 *unit)
{
    if ((u8)UnitField19IsZero(unit) != 0)
        return;
    if ((u8)HasEquippedItemStateProperty(unit, 65) != 0)
        SetUnitStateE8Bit5(unit, 1);
    if ((u8)HasEquippedItemStateProperty(unit, 64) != 0)
        SetUnitStateE8Bit2(unit, 1);
}
