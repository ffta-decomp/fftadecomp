/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DD68.c
 * Original SHA-256: 43bf69c8e906b0baca1a5c22018083a3d59967775572bffc5815887ea6e78724
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct BufferState {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 id;
    u8 unknown_14[2];
    u8 refresh;
    u8 unknown_17;
    const u16 *source;
} BufferState;

extern BufferState data_02007F10;
extern u16 data_02008390[];
extern u16 data_03003860;
extern void func_0814186C(const void *source, void *destination, u32 count);

/* 0801DD68..0801DDB4: 76 bytes, 30 instructions. */
void func_0801DD68(void)
{
    if (data_02007F10.id != 0xff && data_02007F10.enabled != 0) {
        if (data_02007F10.refresh != 0) {
            func_0814186C(data_02007F10.source, data_02008390, 0xa1);
            data_02008390[160] = data_02008390[0];
            data_02007F10.refresh = 0;
        }
        data_03003860 = data_02008390[0];
    }
}
