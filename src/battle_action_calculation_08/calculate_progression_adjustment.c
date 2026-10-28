/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
struct Unit;
extern u32 ReadUnitField(const struct Unit *unit, u8 selector);
extern int UnitField27HasBit13(const struct Unit *unit);
extern int UnitField27HasBit15(const struct Unit *unit);
extern u8 GetGameFlag(u16 flag);
extern u8 ReadSaveByte(u16 index);
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x80c7ea5");
__asm__(".global UnitField27HasBit13\n.thumb_set UnitField27HasBit13, 0x80c8261");
__asm__(".global UnitField27HasBit15\n.thumb_set UnitField27HasBit15, 0x80c8241");
__asm__(".global GetGameFlag\n.thumb_set GetGameFlag, 0x80c9541");
__asm__(".global ReadSaveByte\n.thumb_set ReadSaveByte, 0x80c95a9");


/* Progression/status eligibility followed by a live-field capped adjustment. */
s16 CalculateProgressionValueAdjustment(const struct Unit *source, const struct Unit *other)
{
    u16 flag;
    s16 adjustment;
    u32 other_level;
    if (ReadUnitField(source, 4) > 82) {
        flag = 600;
        switch (ReadUnitField(source, 1)) {
        case 10: break;
        case 9: flag = 601; break;
        case 4: flag = 602; break;
        case 12: flag = 603; break;
        case 94: flag = 604; break;
        default: return 0;
        }
        if ((u8)GetGameFlag(flag) == 0)
            return 0;
        if ((u8)UnitField27HasBit13(source) != 0)
            return 0;
        if ((u8)UnitField27HasBit15(source) != 0)
            return 0;
    }
    if ((u8)ReadSaveByte(13) != 0)
        return 0;
    other_level = ReadUnitField(other, 6);
    adjustment = (other_level - ReadUnitField(source, 6)) * 2U + 10U;
    if (adjustment <= 0)
        adjustment = 1;
    if (adjustment > 100)
        adjustment = 100;
    if (ReadUnitField(source, 6) > 49 && ReadUnitField(source, 7) + adjustment > 99U)
        adjustment = 99U - ReadUnitField(source, 7);
    return adjustment;
}
