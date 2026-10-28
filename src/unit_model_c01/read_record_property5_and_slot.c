/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
extern u8 UnitField27HasBit15(void *unit);
extern u8 UnitQuery_000CB65C(void *unit, int mode);
extern u16 UnitQuery_000CB750(void *unit);

asm(".global UnitQuery_000CB65C\n.thumb_set UnitQuery_000CB65C,0x080cb65d\n.global UnitQuery_000CB750\n.thumb_set UnitQuery_000CB750,0x080cb751");
u16 ReadUnitRecordProperty5AndSlot(void *unit, u8 *output)
{
    if (UnitField27HasBit15(unit))
        *output = UnitQuery_000CB65C(unit, 0);
    else
        *output = UnitQuery_000CB65C(unit, 1);
    return UnitQuery_000CB750(unit);
}
