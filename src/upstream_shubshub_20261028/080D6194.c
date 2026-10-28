/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6194.c
 * Original SHA-256: fc5b4837a4e261ff5a624200176d0f8f630505b8e861617c84d26fed956e7362
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D6194 {
    u8 unknown_00[14];
    u8 flags;
};

extern struct TaskData080D6194 *func_08005BFC(void *task);

/* Complete [0x080D6194, 0x080D61BA): 38 bytes, 18 instructions. */
void func_080D6194(void *task, u8 enabled)
{
    struct TaskData080D6194 *data = func_08005BFC(task);

    if (enabled)
        data->flags |= 2;
    else
        data->flags &= ~2;
}
