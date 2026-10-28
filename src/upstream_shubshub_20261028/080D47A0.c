/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D47A0.c
 * Original SHA-256: a3196f01c4cb7d42884bbec2a649e3dbec78703a122369bc76fd8e38db667823
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D47A0 {
    u8 unknown_00[7];
    u8 flags;
};

extern struct TaskData080D47A0 *func_08005BFC(void *task);

/* Complete [0x080D47A0, 0x080D47C6): 38 bytes, 18 instructions. */
void func_080D47A0(void *task, u8 enabled)
{
    struct TaskData080D47A0 *data = func_08005BFC(task);

    if (enabled)
        data->flags |= 1;
    else
        data->flags &= ~1;
}
