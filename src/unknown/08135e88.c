/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08135E88.c
 * Original SHA-256: 250ffbb2d0573e2fb507138ff24ba0c9307ea01b92a9f388dc631dc30567b50f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* Complete target [0x08135E88, 0x08135F40): 184 bytes, 63 instructions. */
typedef struct {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
} Selection08135E88;

typedef struct {
    u8 unknown_0000[0x8000];
    u16 palettes[2][256];
} Graphics08135E88;

typedef void (*BufferCopier08135E88)(void *, const void *, u32);
extern Selection08135E88 g_state_02000000;
extern Graphics08135E88 *data_0200F3B0;
extern const u8 data_08964838[];
extern const u8 data_089675AC[];
extern u8 data_06010000[];
extern u8 data_06012C00[];
extern const u8 *const data_083A8C54[];
extern BufferCopier08135E88 data_0836D4BC[];
extern void func_0814186C(const void *, void *, u32);

void func_08135E88(void)
{
    func_0814186C(data_08964838, data_06010000, 0x16BC);
    func_0814186C(data_089675AC, data_06012C00, 0x165A);
    data_0836D4BC[0](data_0200F3B0->palettes[0],
                    data_083A8C54[g_state_02000000.mode * 2], 0x200);
    data_0836D4BC[0](data_0200F3B0->palettes[1],
                    data_083A8C54[g_state_02000000.mode * 2 + 1], 0x200);
    data_0200F3B0->palettes[0][0] = 0x7FFF;
}
