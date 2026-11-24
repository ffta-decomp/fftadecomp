typedef unsigned char u8;
typedef unsigned short u16;

extern u8 UnitField19IsZero(const void *unit);

static inline u8 IsStateBitSet(const u8 *flags, u8 mask)
{
    if (*flags & mask)
        return 1;
    return 0;
}

static inline void ClearStateBit(u8 *flags, u8 mask)
{
    *flags &= ~mask;
}

/* Tests the four observed conditions that block the following state clear. */
u8 UnitHasBlockingState(const u8 *unit)
{
    if (UnitField19IsZero(unit)
        || IsStateBitSet(unit + 0xe8, 0x40)
        || IsStateBitSet(unit + 0xea, 0x80)
        || IsStateBitSet(unit + 0xeb, 4))
        return 1;
    return 0;
}

/* Applies the observed exceptions before clearing two transient state bits. */
u8 ClearUnitStateUnlessExcluded(u8 *unit, u16 value)
{
    if (value == 221 || value == 172)
        return 0;
    if (UnitHasBlockingState(unit))
        return 0;
    if (IsStateBitSet(unit + 0xe9, 0x10))
        ClearStateBit(unit + 0xe9, 0x10);
    if (IsStateBitSet(unit + 0xe9, 0x40))
        ClearStateBit(unit + 0xe9, 0x40);
    return 1;
}
