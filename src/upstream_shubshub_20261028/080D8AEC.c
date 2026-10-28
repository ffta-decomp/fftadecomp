/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8AEC.c
 * Original SHA-256: dda911180b0b4f0f3dce714887242ed9aea9e3180ca3dd50bcaf3f46fa8f7ce1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D8AEC..0x080D8B18: 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task)) {
        return 1;
    }
    return 0;
}

void *func_080D8AEC(void *task)
{
    if (task && task_finished(task)) {
        func_08005B58(task);
        return 0;
    }
    return task;
}
