/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020538.c
 * Original SHA-256: 60506aa7dc936730e6e98623afe050b1c93674e15d7c674ce821020b70af6ad6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
    const u8 *current;
} ResourceState08020538;

extern ResourceState08020538 g_state_02007F40;

u32 func_0801F548(const s32 *resource, u16 index);
s32 func_0801F62C(const u32 *table, u16 index);

static inline u32 transfer_idle(void)
{
    return g_state_02007F40.transfer == 0;
}

static inline u32 loader_idle(void)
{
    return g_state_02007F40.current == 0;
}

u32 func_08020538(const s32 *resource, const u32 *table, u16 index)
{
    if (!transfer_idle() || !loader_idle())
        return 0;

    func_0801F548(resource, index);
    func_0801F62C(table, index);
    return 1;
}
