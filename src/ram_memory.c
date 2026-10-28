#include "ram_memory.h"

/* Startup copies this relocation-free code image into IWRAM for Thumb calls. */

/* Clear a positive byte range, using word stores when the destination aligns. */
void ClearBytes(u8 *destination, s32 byte_count)
{
    if (byte_count <= 0)
        return;

    if ((u32)byte_count > 3 && ((u32)destination & 3) == 0) {
        do {
            *(u32 *)destination = 0;
            destination += 4;
            byte_count -= 4;
        } while ((u32)byte_count > 3);

        if (byte_count <= 0)
            return;
    }

    do {
        *destination++ = 0;
    } while (--byte_count > 0);
}

/* Repeat the low byte of value across a range, with aligned word stores. */
void FillBytes(u8 *destination, s32 byte_count, u32 value)
{
    u8 fill = (u8)value;
    u32 repeated;

    if (byte_count <= 0)
        return;

    if ((u32)byte_count > 3 && ((u32)destination & 3) == 0) {
        repeated = fill | ((u32)fill << 8);
        repeated |= repeated << 16;
        do {
            *(u32 *)destination = repeated;
            destination += 4;
            byte_count -= 4;
        } while ((u32)byte_count > 3);

        if (byte_count <= 0)
            return;
    }

    do {
        *destination++ = fill;
    } while (--byte_count > 0);
}

/* Copy a non-overlapping range; word transfers require both pointers aligned. */
void CopyBytes(u8 *destination, const u8 *source, s32 byte_count)
{
    if (byte_count <= 0)
        return;

    if ((u32)byte_count > 3) {
        if (((u32)destination & 3) == 0) {
            if (((u32)source & 3) == 0) {
                do {
                    *(u32 *)destination = *(const u32 *)source;
                    destination += 4;
                    source += 4;
                    byte_count -= 4;
                } while ((u32)byte_count > 3);

                if (byte_count <= 0)
                    return;
            }
        }
    }

    do {
        *destination++ = *source++;
    } while (--byte_count > 0);
}

/* The copied function image ends with a zero halfword, not a Thumb NOP. */
asm(".hword 0");
