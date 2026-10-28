/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08075E24.c
 * Original SHA-256: 3c59910b0d13e251e565dd60c2847d6824f89c20fa27d9453ce4bc554623b56b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_000[0x10c];
    u8 color;
} Display08075E24;

extern Display08075E24 data_030009E0;
extern s32 func_080CA394(const void *object);
extern s32 func_080CA610(void *object);
extern s32 func_080CA5C4(void *object);
extern s32 func_080CA520(const void *object);
extern s32 func_080CA550(const void *object);
extern s32 func_080CA538(const void *object);
extern s32 func_080CA568(const void *object);
extern s32 func_080CA580(const void *object);
extern u32 func_0808B8E4(u32 window, u32 layer, u32 x, u32 y);
extern void func_080899AC(u32 position, u8 color, u32 spacing, u16 value,
                          u32 digits, u32 alignment, u16 tile);

/* 0x08075E24..0x08075FA8: 388 bytes, 167 instructions. */
void func_08075E24(void *object)
{
    u16 tile = 0xd000;
    s32 value;
    u32 position;

    value = func_080CA394(object);
    position = func_0808B8E4(3, 1, 6, 1);
    func_080899AC(position, data_030009E0.color, 100, value, 1, 0, tile);

    value = func_080CA610(object);
    position = func_0808B8E4(0, 1, 6, 9);
    func_080899AC(position, 0x20, 120, value, 1, 0, tile);

    value = func_080CA5C4(object);
    position = func_0808B8E4(3, 1, 12, 2);
    func_080899AC(position, data_030009E0.color, 120, value, 3, 0, tile);

    value = func_080CA520(object);
    position = func_0808B8E4(3, 1, 11, 4);
    func_080899AC(position, data_030009E0.color, 120, value, 3, 0, tile);

    value = func_080CA550(object);
    position = func_0808B8E4(3, 1, 11, 6);
    func_080899AC(position, data_030009E0.color, 100, value, 3, 0, tile);

    value = func_080CA538(object);
    position = func_0808B8E4(0, 1, 11, 14);
    func_080899AC(position, 0x20, 120, value, 3, 0, tile);

    value = func_080CA568(object);
    position = func_0808B8E4(3, 1, 11, 9);
    func_080899AC(position, data_030009E0.color, 100, value, 3, 0, tile);

    value = func_080CA580(object);
    position = func_0808B8E4(0, 1, 11, 17);
    func_080899AC(position, 0x20, 120, value, 3, 0, tile);
}
