#include "ffta/unsigned_types.h"

/* Preserve unsigned-byte wrap; the parent record meaning is tentative. */
u32 AdjustByteUnlessFlagBit1(u8 value, u16 flags)
{
    if (flags & 2)
        return value;
    return (u8)(value + 2);
}
