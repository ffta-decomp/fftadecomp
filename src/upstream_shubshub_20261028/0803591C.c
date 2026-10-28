/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803591C.c
 * Original SHA-256: 0c1864d1ef96d157813dbc1bc88ae1aca6d1b21e73f4f4b113921e56af847e0d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 enabled : 1;
    u8 unknown_01 : 7;
    u8 unknown_01_05[5];
    u8 width;
    u8 unknown_07;
    u8 count;
    u8 unknown_09[3];
    u8 scroll;
} MenuPanel;

typedef struct {
    u32 unknown_00;
    MenuPanel *panel;
    u8 unknown_08[0xF36];
    u8 mode;
} MenuState;

typedef struct {
    u32 unknown_00;
    void *surface;
} RenderState;

typedef struct {
    u8 entry;
    u8 unknown_01[3];
} RenderChoice;

extern MenuState *g_state_03002810;
extern RenderState data_03000E30;
extern const RenderChoice data_08391CA4[];
extern const u8 data_08950258[];
extern const u8 data_089511A4[];
extern const u8 data_08950000[];
extern const u8 data_08950F4C[];

void func_0804C598(void *surface, u32 x, u32 entry, u32 width, u8 count,
                   u32 mode, u32 delay, const u8 *graphics, const u8 *layout, u16 attributes);
void func_0804C4D4(void *surface, u32 x, u32 entry, u32 width, u8 count,
                   u32 mode, u32 delay, const u8 *graphics, const u8 *layout, u16 attributes);

/* Complete target: [0x0803591C, 0x080359E4), 200 bytes. */
void func_0803591C(u32 enabled, u16 choice)
{
    g_state_03002810->panel->enabled = enabled;
    g_state_03002810->mode = 6;
    if (choice == 0) {
        func_0804C598(data_03000E30.surface, 0, 0,
            g_state_03002810->panel->width,
            (u8)(g_state_03002810->panel->count - g_state_03002810->panel->scroll),
            1, 0, data_08950258, data_089511A4, 0xFFA6);
    } else {
        u8 entry = data_08391CA4[choice].entry;
        func_0804C4D4(data_03000E30.surface, 0, entry + 1,
            g_state_03002810->panel->width,
            (u8)(g_state_03002810->panel->count - g_state_03002810->panel->scroll),
            0, 10, data_08950000, data_08950F4C, 0x52);
    }
}
