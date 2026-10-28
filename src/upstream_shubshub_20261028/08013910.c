/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013910.c
 * Original SHA-256: 29199a68ed9e8a53d6c356bac0e68196cd6426bdab6d45ca1ff471c2e1fab784
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08013910..0x080139B8: 168 bytes, 84 instructions. */
typedef struct {
    u8 unknown_00[16];
    u32 rows[16][8];
} WordMatrix;

void func_08013910(WordMatrix *matrix, u32 destination_index, u32 source_index)
{
    u32 *source = &matrix->rows[0][source_index];
    u32 *destination = &matrix->rows[0][destination_index];

    destination[0] = source[0];
    destination[8] = source[8];
    destination[16] = source[16];
    destination[24] = source[24];
    destination[32] = source[32];
    destination[40] = source[40];
    destination[48] = source[48];
    destination[56] = source[56];
    destination[64] = source[64];
    destination[72] = source[72];
    destination[80] = source[80];
    destination[88] = source[88];
    destination[96] = source[96];
    destination[104] = source[104];
    destination[112] = source[112];
    destination[120] = source[120];
}
