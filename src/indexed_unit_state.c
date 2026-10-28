typedef unsigned char u8;
typedef unsigned short u16;

/* Updates one bit in the observed unit state-byte array beginning at +0xe8. */
void SetIndexedUnitState(u8 *unit, u16 index, u8 value)
{
    u8 *flags = &unit[0xe8 + index / 8];
    u8 mask = 1 << (index % 8);

    *flags &= ~mask;
    if (value)
        *flags |= mask;
}
