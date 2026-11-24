/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 ReadUnitField(const void *unit, u8 selector);
extern u8 UnitStateE9HasBit3(const void *unit);

/* Selector 27 reads the halfword at 0x28; the business meaning of its bit remains tentative. */
u32 UnitHasField27Bit11OrStateE9Bit3(const void *unit)
{
    if (ReadUnitField(unit, 27) & 0x800)
        return 1;
    return UnitStateE9HasBit3(unit);
}
