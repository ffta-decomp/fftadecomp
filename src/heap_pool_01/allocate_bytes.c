#include "pool_abi.h"

void *Allocate_08007138(void *storage, u32 byte_count)
{
    u8 *node;
    u32 aligned = byte_count;
    if (byte_count == 0U)
        return (void *)0;
    if ((byte_count & 3U) != 0U)
        aligned = (byte_count & ~3U) + 4U;
    /* Retail keeps only bits2..17 after rounding, including u32 overflow. */
    node = AllocatePoolBlockWords_08006EC0((u8 *)storage, (u16)(aligned >> 2));
    return node != (u8 *)0 ? node + 12U : (void *)0;
}
