typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Preserve unsigned-byte wrap; the parent record meaning is tentative. */
u32 AdjustByteUnlessFlagBit1(u8 value, u16 flags)
{
    if (flags & 2)
        return value;
    return (u8)(value + 2);
}
