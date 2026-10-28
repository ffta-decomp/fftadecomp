/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804CA00.c
 * Original SHA-256: 201fc7c6898b8383d90cb18e541d9ae285e2bf57ee029c7150f2ed750723f757
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804CA00..0x0804CA44: 68 bytes / 26 instructions. */
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 data_0201F550[];
extern u8 *data_0201F53C;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 *func_080070C8(u8 *storage, u32 byte_count);

void func_0804CA00(void)
{
    u32 start = (u32)data_0201F550;
    u32 size;

    if (start & 3) {
        start &= ~3;
        start += 4;
    }
    size = 0x02040000 - start;
    g_callbacks_0836D4B8[0]((void *)start, size);
    data_0201F53C = func_080070C8((u8 *)start, size);
}
