/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E1E0.c
 * Original SHA-256: c8e7b5ed456a64a4d123fb35e284f5a8e3b757effd55b0a60270d4f32d83fa31
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData0804E1E0 {
    u8 unknown_00[6];
    s16 value;
};

extern struct TaskData0804E1E0 *func_08005BFC(void *task);

s16 func_0804E1E0(void *task)
{
    return func_08005BFC(task)->value;
}
