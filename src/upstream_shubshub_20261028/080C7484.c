/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C7484.c
 * Original SHA-256: 4711c3aa6ad0dadbbb778ab684534dd7b4d10a9ee77df5d3000a4668109ae594
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080C7484..0x080C74B4: 48 bytes, 19 instructions, including a pool. */
extern u8 data_030028A0;
extern void *func_08022840(u32 size);
extern void func_080C62CC(void *state, void *first, void *second, u32 mode);

void *func_080C7484(void *first, void *second)
{
    void *state = func_08022840(0xB4);
    func_080C62CC(state, first, second, (data_030028A0 >> 3) & 1);
    return state;
}
