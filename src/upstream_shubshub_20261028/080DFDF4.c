/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DFDF4.c
 * Original SHA-256: 6db275b3157c35f879adfe94cf73443aec24d2d7662eb8798ec1529c60ab37b3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_08005BAC(void *task);
extern void func_08005BA8(void *task, u16 state);

/* Complete [0x080DFDF4, 0x080DFE28): 52 bytes, 21 instructions. */
u8 func_080DFDF4(void *task)
{
    u8 ready = func_08005BAC(task) == 0x101;

    if (!ready)
        return 0;
    func_08005BA8(task, 0x100);
    return 1;
}
