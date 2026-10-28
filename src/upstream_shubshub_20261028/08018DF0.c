/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018DF0.c
 * Original SHA-256: 03d77df74c47d49204341964396c146005d578b3806138b2a174ce65b0f65c3d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08018DF0..0x08018E1E: 46 bytes. */
typedef struct {
    u32 unknown_00;
    const u8 *const *strings;
} TextState08018DF0;

extern TextState08018DF0 g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

u32 func_08018DF0(u8 *destination)
{
    const u8 *const *strings = g_state_020020D0.strings;

    if (strings == 0)
        func_08018C24(destination, g_table_08526680[0]);
    else
        func_08018C24(destination, strings[0]);
    return 0;
}
