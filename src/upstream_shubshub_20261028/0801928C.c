/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801928C.c
 * Original SHA-256: 12ef952fde8d75d7dec30b64730ab34cba577aa5dc06dbbf70311c59130e3b1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TextState {
    u8 unknown_0000[0x21C6];
    u8 text_index;
} TextState;

extern TextState g_state_02000000;
extern const u8 *const data_08569034[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 0801928C..080192C0: 52 bytes, 18 instructions. */
u32 func_0801928C(u8 *destination)
{
    if (g_state_02000000.text_index != 0)
        func_08018C24(destination, data_08569034[g_state_02000000.text_index]);
    return 0;
}
