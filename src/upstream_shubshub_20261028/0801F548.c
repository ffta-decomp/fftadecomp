/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801F548.c
 * Original SHA-256: 4477730dbef3dbe774ca899127bffeb00e52849fb0fec4188c92b808cbf0d460
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801F548..0x0801F62C: 228 bytes, 103 instructions. */
typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
    u8 unknown_16C[4];
    void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

extern ResourceState g_state_02007F40;
extern u8 data_02003CB0[];
extern void func_08141890(const void *source, void *destination);
extern void *func_0801ED24(const void *source, void *relocation_base, u8 flags,
                         u32 mode, u32 x, u32 y, u32 attributes, u32 size);

u32 func_0801F548(const s32 *resource, u16 index)
{
    const s32 *header = resource;
    u16 first_index;
    s32 entry;
    const u8 *source;
    void **relocation_base;

    while (!*header) {
        header++;
    }
    first_index = (*header - 4) >> 2;
    if (g_state_02007F40.transfer) {
        return 0;
    }
    g_state_02007F40.flags = 0;
    relocation_base = &g_state_02007F40.relocation_base;
    entry = resource[first_index];
    *relocation_base = (u8 *)resource + (entry & 0x0FFFFFFF);
    if (entry == -1) {
        *relocation_base = 0;
    } else {
        if (entry < 0) {
            g_state_02007F40.flags = 1;
        }
        if (resource[first_index] & 0x40000000) {
            g_state_02007F40.flags |= 2;
        }
    }
    if (resource[index]) {
        source = (const u8 *)resource + resource[index];
        if (*source) {
            func_08141890(source, data_02003CB0);
            source = data_02003CB0;
        } else {
            source += 4;
        }
        g_state_02007F40.transfer = (void *)source;
        g_state_02007F40.transfer = func_0801ED24(source, g_state_02007F40.relocation_base,
                                       g_state_02007F40.flags, 0, 0, 0, 0, 0x800);
    }
    return 1;
}
