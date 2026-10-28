/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080391C0.c
 * Original SHA-256: 3649fd6840807e24ed345f1336779e6a56194784a9a30a6d5159ee338a6f65c0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 *func_0808B8E4(void *window, u32 layer, u32 x, u32 y);

/* Complete target: [0x080391C0, 0x0803920C), 76 bytes. */
void func_080391C0(void *window, u16 tile)
{
    u16 *map;
    s32 row;
    s32 column;

    tile += 0xc000;
    map = func_0808B8E4(window, 1, 2, 2);
    for (row = 0; row < 7; row++) {
        for (column = 0; column < 14; column++) {
            map[column] = tile++;
            map[column + 27] = tile++;
        }
        map += 54;
    }
}
