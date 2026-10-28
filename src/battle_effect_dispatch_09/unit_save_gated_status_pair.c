/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 ReadSaveByte(u16 index);
extern u8 UnitField27HasBit15(const void *unit);
extern u8 UnitField27HasBit14(const void *unit);

/* Declaration-only target binding from the original direct BL; no helper body. */
asm(".global UnitField27HasBit14\n.thumb_set UnitField27HasBit14, 0x080c82b9");
/* Save byte 13 gates the two observed unit-status predicates. */
u32 UnitPassesSaveGatedStatusPair(const void *unit)
{
    if (ReadSaveByte(13) && UnitField27HasBit15(unit) && UnitField27HasBit14(unit))
        return 1;
    return 0;
}
