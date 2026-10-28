/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813C064.c
 * Original SHA-256: 2d1dcd08742fb3bd9c5a933c5f16751ac85073641f018021b5d3ae2185d387cc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*BufferInitializer0813C064)(void *destination, u32 size);

extern u8 data_0200F3C4[];
extern void *data_0200F3BC;
extern BufferInitializer0813C064 const g_callbacks_0836D4B8[];
extern u8 *func_080070C8(u8 *memory, u32 size);

/* Complete [0x0813C064, 0x0813C0A8): 68 bytes, 26 instructions. */
void func_0813C064(void)
{
    u32 start = (u32)data_0200F3C4;
    u32 size;
    u8 *heap;

    if (start & 3) {
        start &= ~3;
        start += 4;
    }
    size = 0x02040000 - start;
    g_callbacks_0836D4B8[0]((void *)start, size);
    heap = func_080070C8((u8 *)start, size);
    data_0200F3BC = heap;
}
