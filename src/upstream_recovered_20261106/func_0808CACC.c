/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0808CACC.c
 * Original SHA-256: b37446c1f2ae42243f9d17b00c42fbff27cd7047583afba44d5f85d4285afa7f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0xc38];
    u8 enabled;
    u8 ticks;
    u8 counts[3];
    u8 current[3];
    u8 frames[3][3];
    u8 *destinations[3];
} State0808CACC;

extern State0808CACC *data_03002818;
extern u8 data_02003CB0[];
extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_080CBA14(u8 index);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B80C(s32 surface, u16 *tiles, u16 tile, u16 width, u16 flags);
extern void func_0808A604(u32 object, u32 animation);

/* Complete [0x0808CACC, 0x0808CBDC): 272 bytes, 115 instructions. */
void func_0808CACC(void)
{
    int updated = 0;
    int i;
    u8 count;

    if (data_03002818->enabled && data_03002818->ticks++ > 59) {
        data_03002818->ticks = 0;
        for (i = 0; i < 3; i++) {
            if ((count = data_03002818->counts[i]) > 1) {
                int previous = data_03002818->current[i];
                u8 *destination;
                u8 palette;
                int next = previous + 1;

                data_03002818->current[i] = next < count ? next : 0;
                destination = data_03002818->destinations[i];
                func_080CB9E0(data_02003CB0, data_03002818->frames[i][previous]);
                func_0814186C(data_02003CB0, destination, 0x80);
                palette = func_080CBA14(data_03002818->frames[i][previous]);
                func_0808B80C(6, func_0808B8E4(6, 1, 1, i * 4 + 7),
                              0x365 + i * 8, 4, (palette & 15) << 12);
                updated = 1;
            }
        }
        if (updated)
            func_0808A604(6, 2);
    }
}
