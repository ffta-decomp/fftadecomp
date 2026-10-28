/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6180.c
 * Original SHA-256: f76e755f2dd367d9eb0a755b56a0cf1fcdfaf6f4f69935a67732d38cc562744d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D6180 {
    u8 unknown_00[14];
    u8 flags;
};

extern struct TaskData080D6180 *func_08005BFC(void *task);

/* Complete [0x080D6180, 0x080D6192): 18 bytes, 8 instructions. */
void func_080D6180(void *task)
{
    struct TaskData080D6180 *data = func_08005BFC(task);

    data->flags |= 1;
}
