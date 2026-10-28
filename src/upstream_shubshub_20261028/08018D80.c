/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018D80.c
 * Original SHA-256: ae3ca89a0479cbb5a0d5129f0f2fbe28ae10e8e3a21015914e3040a5a9ea10f2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern s32 func_080CA7A4(u16 identifier, u8 selector);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018D80..08018DAC: 44 bytes. */
u32 func_08018D80(u8 *destination)
{
    const u8 *const *strings = g_table_08526680;
    s32 index = func_080CA7A4(g_state_020020D0.identifier, 0);

    func_08018C24(destination, strings[index]);
    return 0;
}
