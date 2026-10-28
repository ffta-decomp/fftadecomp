/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801B888.c
 * Original SHA-256: de8474902509f29b56a66841b641ee10d37b445f681ee4a89f4cf284c8869d9e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State0801B888 {
    u16 unknown_00[22];
    u16 flags;
};

extern struct State0801B888 g_state_02007F40;

/* 0x0801B888..0x0801B898: 16 bytes. */
u32 func_0801B888(void)
{
    return g_state_02007F40.flags & 1;
}
