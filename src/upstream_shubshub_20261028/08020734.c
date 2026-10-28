/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020734.c
 * Original SHA-256: 17b43751884b377b10bba6423b8c77ae64e439e82ac53c74a5b350cf407c1245
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_000[0x168];
    void *transfer;
    u8 unknown_16C[4];
    void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

extern ResourceState g_state_02007F40;
extern void *func_0801ED24(const void *source, void *relocation_base, u8 flags,
                         u32 mode, u32 x, u32 y, u32 attributes, u32 size);

/* 08020734..08020774: 64 bytes. */
void func_08020734(void)
{
    g_state_02007F40.transfer = func_0801ED24(g_state_02007F40.transfer,
        g_state_02007F40.relocation_base, g_state_02007F40.flags,
        0, 0, 0, 0, 0x800);
}
