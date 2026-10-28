/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08121F38.c
 * Original SHA-256: 3494d0fa2d97bea363bc9a2839fbaca72072e0d5a034cf5b7c2755340166cd83
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Queue08121F38 {
    u32 unknown_00;
    u16 entries[4];
    u8 count;
};

extern struct Queue08121F38 data_02002190;
extern void func_08009FD0(void);

/* Complete [0x08121F38, 0x08121F7E): 70 bytes, 31 instructions. */
u8 func_08121F38(void)
{
    struct Queue08121F38 *queue = &data_02002190;
    s32 index;
    u8 result;

    queue->count--;
    for (index = 0; index < queue->count; index++)
        queue->entries[index] = queue->entries[index + 1];
    queue->entries[queue->count] = 0;
    if (queue->count == 0) {
        result = 0;
    } else {
        func_08009FD0();
        result = 1;
    }
    return result;
}
