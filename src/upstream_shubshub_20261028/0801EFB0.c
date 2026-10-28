/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801EFB0.c
 * Original SHA-256: 859f1e7ad7e59727a7bec244549b6b59ed28358312718d80fdbf032eb662141e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801EFB0..0x0801F098: 232 bytes. */
typedef struct {
    u8 unknown_00[0x16C];
    const u8 *source;
    u32 unknown_170;
    const u16 *palette;
} TransferState;

extern TransferState g_state_02007F40;
extern u8 *func_0801AD38(u32 index);

void func_0801EFB0(void)
{
    const u8 *source = g_state_02007F40.source;
    const u16 *palette = g_state_02007F40.palette;
    u8 *base = func_0801AD38(0);
    u16 processed = 0;

    for (;;) {
        u16 offset = source[0] | (source[1] << 8);
        u16 *destination = (u16 *)(base + offset);
        s16 i;
        s16 count;

        source += 2;
        if (palette != 0) {
            count = *source++;

            processed += 3;
            for (i = 0; i < count; i++) {
                u8 index = *source++;

                *destination++ = palette[index];
                processed++;
            }
        } else {
            count = *(const u16 *)source >> 1;

            source += 2;
            processed += 4;
            for (i = 0; i < count; i++) {
                u16 value = source[0] | (source[1] << 8);

                source += 2;
                *destination++ = value;
                processed += 2;
            }
        }

        if ((source[0] | source[1]) == 0) {
            g_state_02007F40.source = 0;
            return;
        }
        if (processed > 0x800)
            break;
    }
    g_state_02007F40.source = source;
}
