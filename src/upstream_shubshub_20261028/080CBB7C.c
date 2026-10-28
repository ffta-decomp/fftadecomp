/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CBB7C.c
 * Original SHA-256: 0fd40b2d13906dd2b367ddb7cc37af3e17288ae2ff205e8a2b4d65db9ce73298
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2FC2];
    u8 mode : 2;
    u8 unknown_2FC2 : 6;
} ResourceState;

extern ResourceState g_state_02000000;
extern const u8 data_0841B060[][32];
extern const u8 data_0841BB40[][32];
extern const u8 data_0841A560[][32];

const u8 *func_080CBB7C(u8 index)
{
    switch (g_state_02000000.mode) {
    case 2:
        return data_0841B060[index];
    case 1:
        return data_0841BB40[index];
    default:
        return data_0841A560[index];
    }
}
