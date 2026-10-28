/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9B08.c
 * Original SHA-256: 2e78919d20e99396711ff9d96d094e284ae5ba431f0a27a30cca914c515ec1e8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D9B08 {
    u32 unknown_00;
    void *object;
};

extern struct TaskData080D9B08 *func_08005BFC(void *task);
extern u32 func_0800C614(void *object);

/* Complete [0x080D9B08, 0x080D9B18): 16 bytes, 6 instructions. */
u32 func_080D9B08(void *task)
{
    return func_0800C614(func_08005BFC(task)->object);
}
