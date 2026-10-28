/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801F62C.c
 * Original SHA-256: 0a734fcac47ff63bff955e7175e6bcbf7346b0cf480f2ebee2c5354d22c559e2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801F62C..0x0801F6C0: 148 bytes. */
typedef struct {
    u8 unknown_00[0x16C];
    const u8 *current;
    u32 unknown_170;
    const u8 *end;
} LoaderState;

extern LoaderState g_state_02007F40;
extern u8 data_02003CB0[];
extern void func_08141890(const void *, void *);
extern void func_0801EFB0(void);

int func_0801F62C(const u32 *table, u16 index)
{
    const u32 *entry = table;
    u16 last;
    u32 last_offset;
    u32 offset;

    while (!*entry)
        entry++;
    last = (*entry - 4) / 4;
    if (g_state_02007F40.current)
        return 0;
    {
        const u8 **end = &g_state_02007F40.end;

        last_offset = table[last];
        *end = (const u8 *)table + last_offset;
        if (last_offset == (u32)-1)
            *end = 0;
    }
    offset = table[index];
    if (offset) {
        const u8 *payload = (const u8 *)table + offset;

        if (*payload) {
            func_08141890(payload, data_02003CB0);
            payload = data_02003CB0;
        } else {
            payload += 4;
        }
        g_state_02007F40.current = payload;
        func_0801EFB0();
    }
    return 1;
}
