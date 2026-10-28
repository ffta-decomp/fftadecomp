/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08067FB0.c
 * Original SHA-256: e5dbc6ec073effb11a1af0e7622653cb38c74982f92b04688228f540448df52f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F3C];
    u16 entries[20];
} EntryState08067FB0;

extern EntryState08067FB0 g_state_02000000;
extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern void func_080CB27C(u8 *buffer);

/* 08067FB0..08067FFC: 76 bytes, 30 reachable instructions. */
u32 func_08067FB0(u32 *output)
{
    u8 *buffer = func_08022840(0x62);
    u32 count;
    u32 state_address;
    const u16 *entry;
    u32 *destination;
    s32 remaining;

    func_080CB27C(buffer);
    count = 0;
    state_address = (u32)&g_state_02000000;
    entry = (const u16 *)(state_address + 0x1F3C);
    destination = output;
    for (remaining = 19; remaining >= 0; remaining--) {
        if (*entry != 0) {
            if (output != 0) {
                *destination = *entry;
            }
            destination++;
            count++;
        }
        entry++;
    }
    func_08022854(buffer);
    return count;
}
