/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013890.c
 * Original SHA-256: eed3edd9a372264df8df25da7f1a6a6baa49e20bbb4ed53ce164c6a0c1b7af51
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct WordMatrix {
    u32 unknown_00;
    u32 *buffer;
    u8 unknown_08[8];
    u32 rows[16][8];
} WordMatrix;

/* 08013890..08013910: 128 bytes, 64 instructions. */
void func_08013890(WordMatrix *matrix, u32 source_index, u32 destination_index)
{
    u32 *source = &matrix->rows[0][source_index];
    u32 *destination = matrix->buffer + destination_index * 16;

    destination[0] = source[0];
    destination[1] = source[8];
    destination[2] = source[16];
    destination[3] = source[24];
    destination[4] = source[32];
    destination[5] = source[40];
    destination[6] = source[48];
    destination[7] = source[56];
    destination[8] = source[64];
    destination[9] = source[72];
    destination[10] = source[80];
    destination[11] = source[88];
    destination[12] = source[96];
    destination[13] = source[104];
    destination[14] = source[112];
    destination[15] = source[120];
}
