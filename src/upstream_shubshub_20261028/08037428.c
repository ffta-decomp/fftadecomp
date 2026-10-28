/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08037428.c
 * Original SHA-256: b5fae7aa3d6273da999cae91f78c7bdb9f4e0c2e5a32d5d07020fb3401b1bf4d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef union {
    u8 raw;
    struct {
        u8 unknown_00 : 2;
        u8 position : 3;
        u8 unknown_05 : 3;
    } bits;
} CursorFlags08037428;

typedef struct {
    CursorFlags08037428 flags;
    u8 unknown_04[2];
    s16 x;
    s16 y;
} Cursor08037428;

typedef struct {
    u16 unknown_00;
    u16 x;
    u16 y;
    u8 unknown_06[0x2e];
} CursorPosition08037428;

typedef struct {
    u8 unknown_00[4];
    Cursor08037428 *cursor;
    u8 unknown_08[0x7d8];
    CursorPosition08037428 positions[8];
    u8 unknown_980[0x5ba];
    u8 held_ticks;
    u8 acceleration;
    u8 cooldown;
    u8 unknown_f3d;
    u8 disabled;
} CursorState08037428;

extern u16 data_03000000;
extern CursorState08037428 *g_state_03002810;

#define CLAMP_LOW(value, limit) ((value) > (limit) ? (value) : (limit))
#define CLAMP_HIGH(value, limit) ((value) > (limit) ? (limit) : (value))
#define CURSOR_STEP (!(data_03000000 & 2) ? 1 + g_state_03002810->acceleration : 4)

void func_08037428(void)
{
    u16 directions = data_03000000 & 0xf0;
    u8 locked;

    if (g_state_03002810->disabled)
        return;
    locked = g_state_03002810->cursor->flags.raw & 2;
    if (locked) {
        g_state_03002810->cursor->x =
            g_state_03002810->positions[g_state_03002810->cursor->flags.bits.position].x + 6;
        g_state_03002810->cursor->y =
            g_state_03002810->positions[g_state_03002810->cursor->flags.bits.position].y + 4;
        return;
    }

    if (directions == 0) {
        g_state_03002810->acceleration = 0;
        g_state_03002810->held_ticks = 0;
    } else if (g_state_03002810->held_ticks > 0x3c) {
        g_state_03002810->acceleration = 3;
    } else if (g_state_03002810->held_ticks++ > 0xa) {
        g_state_03002810->cooldown = 0;
        g_state_03002810->acceleration = 1;
    }
    if (directions != 0 && g_state_03002810->cooldown != 0)
        g_state_03002810->cooldown--;

    if (directions & 0x20)
        g_state_03002810->cursor->x = CLAMP_LOW(g_state_03002810->cursor->x - CURSOR_STEP, 14);
    else if (directions & 0x10)
        g_state_03002810->cursor->x = CLAMP_HIGH(g_state_03002810->cursor->x + CURSOR_STEP, 224);
    if (directions & 0x40)
        g_state_03002810->cursor->y = CLAMP_LOW(g_state_03002810->cursor->y - CURSOR_STEP, 22);
    else if (directions & 0x80)
        g_state_03002810->cursor->y = CLAMP_HIGH(g_state_03002810->cursor->y + CURSOR_STEP, 330);
}
