/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081164E8.c
 * Original SHA-256: 3c1a8329b1038060cd7dfe19ec7cd206c40b77da4c55f63aa41d36acb60546fb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x081164E8, 0x08116514), 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_is_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_081164E8(void *task)
{
    if (task != 0) {
        if (task_is_finished(task)) {
            func_08005B58(task);
            return 0;
        }
    }
    return task;
}
