/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801F124.c
 * Original SHA-256: aa230c2350bd35f49e26fee34154aa62a8dcf698f15a8e1c81a7090674c8c6d2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x168];
    const void *transfer;
    u8 unknown_16C[4];
    const void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

extern ResourceState g_state_02007F40;

/* 0801F124..0801F1A8: 132 bytes, 62 instructions. */
void func_0801F124(const u32 *resource)
{
    u32 header;

    g_state_02007F40.flags = 0;
    header = *resource;
    if (header & 0x80000000) {
        g_state_02007F40.transfer = resource + 1;
        g_state_02007F40.relocation_base = (const u8 *)resource +
                                 (header & 0x0FFFFFFF);
        g_state_02007F40.flags = 1;
    } else {
        g_state_02007F40.transfer = resource + 1;
        g_state_02007F40.relocation_base = 0;
    }
    if (*resource & 0x40000000)
        g_state_02007F40.flags |= 2;
    g_state_02007F40.flags |= 4;
}
