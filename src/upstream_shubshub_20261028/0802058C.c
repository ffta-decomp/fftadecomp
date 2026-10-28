/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802058C.c
 * Original SHA-256: 48358ac39c83781d2ba198cddf4877b30d3b0f28a59db6865a075b45a23bba81
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0802058C..0x080205C8: 60 bytes. */
typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
    const u8 *current;
} ResourceState;

extern ResourceState g_state_02007F40;

static inline u32 transfer_idle(void)
{
    return g_state_02007F40.transfer == 0;
}

static inline u32 loader_idle(void)
{
    return g_state_02007F40.current == 0;
}

u32 func_0802058C(void)
{
    u32 ready = 0;

    if (transfer_idle() && loader_idle()) {
        ready = 1;
    }
    return ready;
}
