/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3958.c
 * Original SHA-256: 0a4212f6efc3c5bee102f05615f1e8f26c394459601d5f691ef503592cf91ffe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D3958 {
    u32 unknown_00[2];
    u32 value;
};

extern void *data_020159C0;
extern struct TaskData080D3958 *func_08005BFC(void *task);

/* Complete [0x080D3958, 0x080D3970): 24 bytes, 9 instructions. */
void func_080D3958(u32 value)
{
    func_08005BFC(data_020159C0)->value = value;
}
