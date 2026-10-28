/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
struct Unit;
extern u32 UnitField(const struct Unit *, u8);
extern u8 SaveByte(u16);
extern s32 StatusBit15(const struct Unit *);
extern u8 MissionPercentage(u8);
__asm__(".thumb_set UnitField, 0x080c7ea5");
__asm__(".thumb_set SaveByte, 0x080c95a9");
__asm__(".thumb_set StatusBit15, 0x080c8241");
__asm__(".thumb_set MissionPercentage, 0x080d2bf5");
__asm__(".thumb_set __divsi3, 0x081426b9");


/* Select field24/26 and apply the source-proven mission percentage gate. */
s32 ReadMissionAdjustedUnitField(const struct Unit *unit, u16 alternate)
{
    s32 value;
    u8 percentage;
    if (alternate == 0) {
        value = UnitField(unit, 24);
        if ((u8)SaveByte(13) != 0)
            goto done;
        if ((u8)StatusBit15(unit) != 0)
            goto done;
        percentage = MissionPercentage(11);
        value = (u32)value + (s32)((u32)value * percentage) / 100;
    } else {
        value = UnitField(unit, 26);
        if ((u8)SaveByte(13) != 0)
            goto done;
        if ((u8)StatusBit15(unit) != 0)
            goto done;
        percentage = MissionPercentage(13);
        value = (u32)value + (s32)((u32)value * percentage) / 100;
    }
done:
    return value;
}
