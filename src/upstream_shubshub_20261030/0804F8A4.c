/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0804F8A4.c
 * Original SHA-256: 997f03f94a5304f531ce33d93711b8524b8212ec8ccf9cbd75cac3aef9614b93
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef signed short s16;

typedef struct {
    u8 unknown_000[0x562];
    u8 column;
    u8 row;
} Selection;

typedef struct {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 value;
    u8 extra;
    s16 timer;
} DrawState;

typedef struct {
    Selection *selection;
    u8 unknown_04[7];
    u8 active;
    u8 unknown_0C[0x90];
    DrawState marker;
    DrawState first_arrow;
    DrawState second_arrow;
} SelectionDisplay;

extern void func_08017FE8(const DrawState *state);

/* Complete [0x0804F8A4, 0x0804F938): 148 bytes, including literal pools. */
void func_0804F8A4(SelectionDisplay *display)
{
    if (display->active) {
        display->marker.x = display->selection->column * 32 + 16;
        display->marker.y = display->selection->row * 32 + 68;
        func_08017FE8(&display->marker);
        display->first_arrow.timer++;
        if (display->first_arrow.timer > 5) {
            display->first_arrow.timer = 0;
            display->first_arrow.offset_x++;
            if (display->first_arrow.offset_x > 2)
                display->first_arrow.offset_x = 0;
            display->second_arrow.offset_x--;
            if (display->second_arrow.offset_x <= -3)
                display->second_arrow.offset_x = 0;
        }
        func_08017FE8(&display->first_arrow);
        func_08017FE8(&display->second_arrow);
    }
}
