/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DAE44.c
 * Original SHA-256: 2b3c72b99bba90621ff2e5d35199bee47b2be460d0d91b2f26f972e88cf058ee
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080DAE44, 0x080DAE70), 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_080DAE44(void *task)
{
    if (task != 0 && task_finished(task))
    {
        func_08005B58(task);
        return 0;
    }
    return task;
}
