/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08136538.c
 * Original SHA-256: 0440e07b7d88cdbbc0f7a5c3320246ae2d5bf67cf59f5cbec0d1cbed6004f2ab
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08136538, 0x08136868): 816 bytes, 339 instructions. */
typedef struct {
    const void *image;
    u8 mode;
    u8 unknown_05[5];
    u16 y;
    u16 target_x;
    u16 target_y;
    u16 width;
    u16 height;
    u8 unknown_14[8];
} Item08136538;

typedef struct {
    u8 phase;
    u8 next_phase;
    u16 timer;
    u16 index;
    u8 unknown_06[2];
    Item08136538 items[19];
} State08136538;

typedef struct {
    void *first;
    u8 *source;
    u16 count;
    u8 unknown_0a[2];
    u16 *data;
    u16 index;
    u16 frame;
    u16 entry;
    u8 wrap;
    u8 unknown_17;
    u16 finished;
} Animation08136538;

typedef struct {
    u8 unknown_0000[0x8954];
    u8 visible;
    u8 unknown_8955;
    s16 x;
    s16 y;
    u8 unknown_895a[0x12];
    Animation08136538 animation;
    u8 unknown_8988;
    u8 exiting;
    u8 fade;
} Context08136538;

extern Context08136538 *data_0200F3B0;
extern u16 data_03000000[];
extern const void *data_083A8D60[];
extern u16 data_083A8DAC[][2];
extern u16 data_083A8DFA[][2];
extern u16 data_083A8DF8[];
extern u8 data_089A0390[];
extern u8 data_089A031C[];
extern void func_08135FFC(Animation08136538 *, void *, u8 *, u16, u8);
extern void *func_08136028(Animation08136538 *);
typedef struct PaletteTransition PaletteTransition;

extern PaletteTransition *func_08147AD0(u16 first, u16 count, u16 duration);
extern void func_081369EC(PaletteTransition *transition);
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                         u32, u32, u32, u32);
extern void func_08136868(Item08136538 *);
extern void func_08136944(Item08136538 *);

u32 func_08136538(State08136538 *state)
{
    u8 i;

    switch (state->phase) {
    case 0:
        data_0200F3B0->exiting = 0;
        func_08135FFC(&data_0200F3B0->animation, data_089A0390,
                     data_089A031C, 0, 0);
        for (i = 0; i < 19; i++) {
            state->items[i].image = data_083A8D60[i];
            state->items[0].mode = 0;
        }
        data_0200F3B0->visible = 0;
        state->index = 0;
        state->phase = 1;
        state->timer = 0;
        break;
    case 1:
        state->timer++;
        if (state->timer > 2) {
            state->items[state->index].target_x = 120;
            state->items[state->index].target_y = 120;
            state->items[state->index].width = data_083A8DAC[state->index][0];
            state->items[state->index].height = data_083A8DAC[state->index][1];
            state->items[state->index].mode = 1;
            state->timer = 0;
            state->index++;
            if (state->index > 18) {
                state->phase = 100;
                state->next_phase = 5;
                state->timer = 30;
            }
        }
        break;
    case 5:
        data_0200F3B0->visible = 1;
        state->phase = 100;
        state->next_phase = 10;
        state->timer = 30;
        data_0200F3B0->x = 64;
        data_0200F3B0->y = 67;
        break;
    case 10:
        for (i = 0; i < 19; i++) {
            state->items[i].target_y = data_083A8DFA[i][0];
            state->items[i].height = data_083A8DFA[i][0] - 42;
            state->items[i].mode = 3;
            state->timer = 0;
        }
        state->phase = 11;
        break;
    case 11:
    {
        Context08136538 *context = data_0200F3B0;
        int y = state->items[0].y - 28;
        context->y = y + data_083A8DF8[1];
        state->timer++;
        if (state->timer > 50) {
            state->phase = 100;
            state->next_phase = 20;
            state->timer = 5;
        }
        break;
    }
    case 20:
        if (!data_0200F3B0->exiting) {
            func_081369EC(func_08147AD0(0, 512, 2));
            data_0200F3B0->exiting = 1;
            data_0200F3B0->fade = 0;
            state->phase = 0xff;
        }
        break;
    case 100:
        if (state->timer == 0)
            state->phase = state->next_phase;
        else
            state->timer--;
        break;
    }

    if (data_03000000[1] & 8) {
        if (!data_0200F3B0->exiting) {
            func_081369EC(func_08147AD0(0, 512, 2));
            data_0200F3B0->fade = 0;
            data_0200F3B0->exiting = 1;
        }
    }
    if (data_0200F3B0->exiting) {
        data_0200F3B0->fade++;
        if (data_0200F3B0->fade > 8)
            return 1;
    }
    if (data_0200F3B0->visible) {
        const void *image = func_08136028(&data_0200F3B0->animation);
        func_08001F34(image, data_0200F3B0->x, data_0200F3B0->y,
                     0, 0, 0, 0, 0, 0, 0, 0);
    }
    for (i = 0; i < 19; i++) {
        func_08136868(&state->items[i]);
        func_08136944(&state->items[i]);
    }
    return 0;
}
