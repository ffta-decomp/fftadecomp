/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804ADC8.c
 * Original SHA-256: 4c209e31ee7ecf2c5ec757d923d132ee538f6a00b46ff55eae76fbe72fabbe97
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 unknown_000[0xF1C];
    u8 count;
    u8 state;
    u8 unknown_F1E;
    u8 selection;
    u8 previous_selection;
    u8 flags;
} MenuState;

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_tiles;
    u16 *second_tiles;
    u8 unknown_20[8];
    u8 width;
    u8 unknown_29[0x23];
} Tilemap;

extern MenuInput data_03000000;
extern MenuState *g_state_03002810;
extern Tilemap data_030009E0[];
extern void func_08141540(u32 sound);
extern void func_0808A008(u16 *tiles, u32 stride, u32 width, u32 height,
                         u32 rows, u32 palette);
extern void func_0808A604(u32 object, u32 command);

/* Complete [0x0804ADC8, 0x0804AFE0): 536 bytes, 229 reachable Thumb instructions. */
u32 func_0804ADC8(u32 object, u32 arg1, u32 arg2, u32 flags)
{
    u32 result = 0;

    if (flags & 1) {
        u16 keys;

        if (g_state_03002810->flags & 0x40)
            keys = data_03000000.repeated & 0x30;
        else
            keys = data_03000000.repeated & 0xC0;
        if (keys & 0x90) {
            if (++g_state_03002810->selection >= g_state_03002810->count) {
                if (g_state_03002810->flags & 0x20) {
                    if (!(flags & 2))
                        func_08141540(0x6D);
                    g_state_03002810->selection = 0;
                } else {
                    g_state_03002810->selection = g_state_03002810->count - 1;
                }
            } else if (!(flags & 2)) {
                func_08141540(0x6D);
            }
        } else if (keys & 0x60) {
            if (--g_state_03002810->selection == 0xFF) {
                if (g_state_03002810->flags & 0x20) {
                    if (!(flags & 2))
                        func_08141540(0x6D);
                    g_state_03002810->selection = g_state_03002810->count - 1;
                } else {
                    g_state_03002810->selection = 0;
                }
            } else if (!(flags & 2)) {
                func_08141540(0x6D);
            }
        } else if (data_03000000.pressed & 1) {
            result = 1;
        } else if (data_03000000.pressed & 2) {
            result = 2;
        }
        if (object && g_state_03002810->selection != g_state_03002810->previous_selection &&
            !(g_state_03002810->flags & 0x80)) {
            if (g_state_03002810->previous_selection != 0xFF)
                func_0808A008(data_030009E0[object].second_tiles +
                              data_030009E0[5].width *
                              (g_state_03002810->previous_selection * 2 + 2),
                              2, data_030009E0[5].width, data_030009E0[5].width, 2, 0xC000);
            func_0808A008(data_030009E0[object].second_tiles +
                          data_030009E0[5].width * (g_state_03002810->selection * 2 + 2),
                          2, data_030009E0[5].width, data_030009E0[5].width, 2, 0xB000);
            func_0808A604(object, 2);
        }
    }
    g_state_03002810->previous_selection = g_state_03002810->selection;
    return result;
}
