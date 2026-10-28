/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F060.c
 * Original SHA-256: 8ba6a46ef49c1d5aa13493ba5d33084e967ae858e99c22ba1d4a4cbc8c0bf9b4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804F060..0x0804F0F2: 146 bytes, 59 instructions. */
typedef struct {
    u8 unknown_00;
    u8 palette;
    u8 unknown_02[4];
    u16 image_count;
    u8 unknown_08[0x55C];
    u8 image_data[1];
} MenuPanel;

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 flags;
    u8 unknown_11[3];
} CursorState;

typedef struct {
    MenuPanel *panel;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[0x5F];
    CursorState upper;
    CursorState lower;
} MenuState;

typedef void (*MenuCallback)(void);

extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_08019A8C(const void *images, u16 count, void *a, void *b);
extern void func_08013404(MenuCallback first, MenuCallback second);
extern void func_08017D18(CursorState *cursor, u32 mode);
extern void func_08050D50(void);
extern void func_08050DA0(void);

static inline void prepare_cursor(CursorState *cursor)
{
    if (cursor) {
        if (cursor->x <= 224 && cursor->y <= 64) {
            cursor->flags &= ~4;
        }
        cursor->flags |= 64;
    }
}

void func_0804F060(MenuState *state)
{
    CursorState *upper = &state->upper;
    CursorState *lower = &state->lower;

    func_08019A8C(state->panel->image_data, state->panel->image_count,
                  data_030008B0, data_03000990);
    switch (state->mode) {
    case 1:
    case 4:
    case 5:
        func_08013404(func_08050D50, func_08050DA0);
        break;
    }
    state->panel->palette = upper->flags;
    if (upper->y + upper->height <= 64) {
        func_08017D18(upper, 0);
    } else {
        func_08017D18(upper, 1);
    }
    prepare_cursor(lower);
}
