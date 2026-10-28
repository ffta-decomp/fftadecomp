/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EEF6C.c
 * Original SHA-256: f4a10179b59343fa452803a20512fc666ddcf7c15bab4e83f5bfc93c091e2c60
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080EEF6C .. 0x080EEF98: 44 bytes. */
extern int func_08005BB0(const void *);
extern void func_08005B58(void *);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_080EEF6C(void *task)
{
    void *result;

    if (task && task_finished(task)) {
        func_08005B58(task);
        result = 0;
    } else {
        result = task;
    }
    return result;
}
