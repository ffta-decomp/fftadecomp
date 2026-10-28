/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 UnitField27HasBit15(const void *unit);
extern u8 LoadUnitRecordSlot(const void *unit, u8 selector);
extern u16 ReadUnitRecordProperty04(const void *unit);
/* Declaration-only bindings from the original three direct BL targets. */
asm(".global LoadUnitRecordSlot\n.thumb_set LoadUnitRecordSlot,0x080cb65d\n.global ReadUnitRecordProperty04\n.thumb_set ReadUnitRecordProperty04,0x080cb715");


/* Both branch calls join at their byte store, before the property read. */
u16 ReadUnitRecordPropertyAndSlot(const void *unit, u8 *slot)
{
    if ((u8)UnitField27HasBit15(unit) != 0)
        *slot = LoadUnitRecordSlot(unit, 0);
    else
        *slot = LoadUnitRecordSlot(unit, 1);
    return ReadUnitRecordProperty04(unit);
}
