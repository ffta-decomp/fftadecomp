/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813C0A8.c
 * Original SHA-256: 8f47e3d5c3aec6aa66311d15070585937f732dadece1e473abbaf5a5812fe2e7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813C0A8..0x0813C0C4: 28 bytes, 11 instructions. */
extern void *data_0200F3BC;
extern void func_0800718C(void *owner);

void func_0813C0A8(void)
{
    if (data_0200F3BC) {
        func_0800718C(data_0200F3BC);
        data_0200F3BC = 0;
    }
}
