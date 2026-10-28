/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetGameFlag(u16);
extern u32 UnitStateEAHasBit3(const u8 *);
extern u32 UnitStateEBHasBit7(const u8 *);
extern u32 UnitStateEBHasBit6(const u8 *);
asm(".global GetGameFlag\n.thumb_set GetGameFlag,0x080c9541\n.global UnitStateEAHasBit3\n.thumb_set UnitStateEAHasBit3,0x080cdbcd\n.global UnitStateEBHasBit7\n.thumb_set UnitStateEBHasBit7,0x080cdb9d\n.global UnitStateEBHasBit6\n.thumb_set UnitStateEBHasBit6,0x080cdb85");

u32 UnitPassesSideFlagRule(const u8 *unit)
{
    if (((u8)GetGameFlag(3) && (u8)GetGameFlag(4)) || (u8)UnitStateEAHasBit3(unit))
        return 0;
    if ((u8)GetGameFlag(3) || (u8)GetGameFlag(4)) {
        if ((u8)GetGameFlag(4)==1 && !(u8)GetGameFlag(3)) {
            if ((u8)UnitStateEBHasBit7(unit))
                return 0;
        } else if (!(u8)GetGameFlag(4) && (u8)GetGameFlag(3)==1) {
            if ((u8)UnitStateEBHasBit6(unit))
                return 0;
        }
    }
    return 1;
}
