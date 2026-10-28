/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018DAC.c
 * Original SHA-256: 4bc9871a0e253ff59adab5c8eba20e4c2010570378b04fbc5151774f383f2c25
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TextState {
    u8 unknown_00[0x0E];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *g_table_08526680[];
extern u16 func_080CA7A4(u16 identifier, u32 mode);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018DAC..08018DF0: 68 bytes, 26 instructions. */
u32 func_08018DAC(u8 *destination)
{
    u16 index;

    if (g_state_020020D0.identifier <= 0x178)
        index = func_080CA7A4(g_state_020020D0.identifier, 0);
    else
        index = g_state_020020D0.identifier + 0x7B;
    func_08018C24(destination, g_table_08526680[index]);
    return 0;
}
