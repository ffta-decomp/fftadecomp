/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0808B92C.c
 * Original SHA-256: 401382468f708331e722f6c6faf794a467ef0a57ca102c1423e444dd7f016813
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct TileLayout0808B92C {
    u8 unknown_00[0x2C];
    u8 row_stride;
    u8 unknown_2D[0x1F];
} TileLayout0808B92C;

extern TileLayout0808B92C data_030009E0[];

/* Complete [0x0808B92C, 0x0808B950): 36 bytes, 16 instructions. */
u8 *func_0808B92C(u32 index, u8 *tiles, u32 column, u32 row)
{
    return tiles + ((data_030009E0[index].row_stride * row + column * 2) << 5);
}
