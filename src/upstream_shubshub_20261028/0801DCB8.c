/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DCB8.c
 * Original SHA-256: 47fff5001c22996df405d80bf4ea5bfe8717ce4df894ca36c048bb595a43d0e6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TransferState {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
    u8 unknown_14[2];
    u8 pending;
    u8 unknown_17;
    const u16 *source;
} TransferState;

extern TransferState data_02007F10;
extern u16 data_03003860;
extern u16 data_02008390[161];
extern void func_0814186C(const void *source, void *destination, u32 count);

/* 0801DCB8..0801DD00: 72 bytes, 29 instructions. */
void func_0801DCB8(const u16 *source)
{
    if (data_02007F10.selector == 0xFF)
        return;
    if (data_02007F10.enabled) {
        data_02007F10.pending = 1;
        data_02007F10.source = source;
        data_03003860 = source[0];
    } else {
        func_0814186C(source, data_02008390, 161);
        data_02008390[160] = data_02008390[0];
    }
}
