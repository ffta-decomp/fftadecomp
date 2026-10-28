/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808EEE8.c
 * Original SHA-256: 1165cef56e4377b1e41d52e58d5261827bee4c8069284d1ad91caf2c1601e7cd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 func_080CBA14(u8 id);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B80C(u32 index, u16 *destination, u16 tile, u32 height, u16 palette);

/* Complete [0x0808EEE8, 0x0808EF4A): 98 bytes, 46 instructions. */
void func_0808EEE8(s32 x, s32 y, u32 id, u32 mode)
{
    u16 palette = func_080CBA14(id);
    u16 *destination;

    if (mode == 0)
        palette -= 13;

    destination = func_0808B8E4(1, 1, x * 4 + 1, y * 3 + 2);
    func_0808B80C(1, destination, (id - 2) * 8 + 1, 4, palette << 12);
}
