/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F1210.c
 * Original SHA-256: 52089a5c1ff70710d60e90198120b8c29220e0d7d2babc4d6600bb0c38ff7b66
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080F1210..0x080F123C: 44 bytes, 20 instructions. */
extern u32 func_08005BB0(void *task);
extern void func_08005B58(void *task);

static inline u8 task_is_finished(void *task)
{
    if (func_08005BB0(task)) {
        return 1;
    }
    return 0;
}

void *func_080F1210(void *task)
{
    if (task && task_is_finished(task)) {
        func_08005B58(task);
        return 0;
    }
    return task;
}
