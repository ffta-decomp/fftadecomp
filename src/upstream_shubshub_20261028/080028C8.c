/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080028C8.c
 * Original SHA-256: a4367c9b706bd94c1ca5161a5e882c9d0adf9dab5237bf1edc1f3ea28b186993
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef s32 (*Compare)(const void *first, const void *second);

extern void func_08002524(void *workspace, void *base, s32 size, s32 count,
                          Compare compare);

/* 080028C8..080028E2: 26 bytes, 12 instructions. */
void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                   Compare compare)
{
    func_08002524(workspace, base, size, count, compare);
}
