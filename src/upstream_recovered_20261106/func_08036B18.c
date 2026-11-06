/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08036B18.c
 * Original SHA-256: 0313a325e6a57e4215243d3194531733790dad619666828650889a236ba8dd57
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u16 unknown_00 : 7;
    u16 field_07 : 2;
    u16 unknown_09 : 7;
    u8 unknown_02[0xA];
    u16 scroll;
} Panel08036B18;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} Position08036B18;

typedef struct {
    u32 unknown_00;
    Panel08036B18 *panel;
    u8 unknown_08[0x674];
    Position08036B18 *positions;
} Menu08036B18;

typedef struct {
    u8 unknown_00[0x2E54];
    unsigned selection : 5;
    unsigned unknown_05 : 3;
} Selection08036B18;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} Renderer08036B18;

extern Menu08036B18 *g_state_03002810;
extern Selection08036B18 g_state_02000000;
extern Renderer08036B18 data_03000E30;
extern u8 data_02003CB0[];
extern const u8 data_083AD154[];
extern u8 data_060124C0[];
extern const u8 data_089508D8[];
extern const u8 data_08951460[];
extern u8 *func_0800543C(void *destination, const void *source);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0804C4D4(Entry *, u16, u16, u8, u8, u8, u8,
                         const u8 *, const u8 *, u16);
extern void func_0804C598(Entry *, u16, u16, u8, u8, u8, u8,
                         const u8 *, const u8 *, u16);

/* Complete target: [0x08036B18, 0x08036CA8), 400 bytes. */
void func_08036B18(u32 mode)
{
    u8 *buffer = data_02003CB0;
    s32 clipped = 0;
    s32 selected = g_state_02000000.selection - 1;
    s32 pixel_x = g_state_03002810->positions[selected].x * 8;
    s32 x = pixel_x + 8;
    s32 y = g_state_03002810->positions[selected].y * 8 - g_state_03002810->panel->scroll - 24;

    if (x < 24)
        x = 24;
    else if (pixel_x + 32 > 240)
        x = 216;

    if (y < 10) {
        y = 10;
        clipped = 10;
    } else if (y > 136) {
        y = 136;
    }

    if (mode == 1) {
        func_0800543C(buffer, data_083AD154);
        func_0814186C(buffer, data_060124C0, 0x4E0);
        if (!clipped)
            func_0804C598(data_03000E30.surface, 3, 0, x, y, 0, 10,
                           data_089508D8, data_08951460, 0x126);
        else
            func_0804C4D4(data_03000E30.surface, 3, 0, x, y, 0, 10,
                           data_089508D8, data_08951460, 0x126);
    } else if (mode == 2) {
        func_0800543C(buffer, data_083AD154);
        func_0814186C(buffer, data_060124C0, 0x4E0);
        if (!clipped)
            func_0804C598(data_03000E30.surface, 3, 0, x, y, 0, 10,
                           data_089508D8, data_08951460, 0x126);
        else
            func_0804C4D4(data_03000E30.surface, 3, 0, x, y, 0, 10,
                           data_089508D8, data_08951460, 0x126);
    }
    g_state_03002810->panel->field_07 = 0;
}
