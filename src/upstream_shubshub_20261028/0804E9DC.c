/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E9DC.c
 * Original SHA-256: d47b705760e9766cad95b33e777b6de9751367af7852c4c373fed654dd21e3d2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804E9DC..0x0804E9EE: 18 bytes / 8 instructions. */
struct TaskPayload0804E9DC {
    u8 unknown_00[4];
    u16 flags;
};

extern struct TaskPayload0804E9DC *func_08005BFC(void *task);

void func_0804E9DC(void *task)
{
    struct TaskPayload0804E9DC *payload = func_08005BFC(task);

    payload->flags |= 1;
}
