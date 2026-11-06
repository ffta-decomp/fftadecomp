/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08009140.c
 * Original SHA-256: 1bb5e6f1024b7bb4ac7478888867ccd41dae7016b75fa4f259536fa8512146bf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
/* 0x08009140 - 316 target bytes, including four internal literal words. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x15];
    u8 field_15;
    u8 unknown_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u16 field_1C;
} ClampState08017B9C;

typedef struct {
    u8 unknown_00[0x10];
    u8 (*rows)[32];
} Display08009140;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} Panel08009140;

typedef struct {
    u8 current;
    u8 count;
    u8 unknown_02;
    u8 enabled;
} Entry08009140;

typedef struct {
    u8 unknown_00[0x18];
    Display08009140 *display;
    u8 unknown_1C[0x2d4];
    ClampState08017B9C control;
    Panel08009140 panel;
    u8 unknown_324[0x14];
    Entry08009140 entries[10];
    u8 unknown_360[0x186c];
    u8 settings[4];
} State08009140;

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeated;
} Input08009140;

s32 func_080096B0(const void *first, const void *second, s32 size);
void func_08141570(s32 player_id, u16 song_id);
u16 func_08017B68(ClampState08017B68 *state, u32 index);
u16 func_08017B9C(ClampState08017B9C *state, u32 index);
u8 func_080094BC(u8 index, u8 query);
u8 func_08009030(u8 index, u8 *destination);
void func_08008F94(s8 index);
void func_08141540(u16 sound);
u8 func_0800927C(u16 input);

extern State08009140 *data_02009188;
extern Input08009140 data_03000000;
extern const u8 g_object_02002FC0[];

u8 func_08009140(void)
{
    State08009140 **current = &data_02009188;
    Panel08009140 *panel = &(*current)->panel;
    ClampState08017B9C *control = &(*current)->control;
    Input08009140 *input = &data_03000000;
    u16 pressed = input->pressed;
    u16 repeated = input->repeated;
    u16 selected;
    u8 *destination;
    Entry08009140 *entry;
    u8 previous;

    if (pressed & 2) {
        if (func_080096B0((*current)->settings, g_object_02002FC0, 4) == 0) {
            func_08141570(1, 0x69);
            return 2;
        }
        return 4;
    }
    if (pressed & 1) {
        selected = func_08017B68((ClampState08017B68 *)control, panel->selection);
        destination = (*current)->display->rows[
            func_08017B9C(control, panel->selection)];
        entry = &(*current)->entries[(s16)selected];
        if (entry->enabled == 0) {
            func_08141570(1, 0x6b);
            return 0;
        }
        if (entry->count == 0)
            return 3;
        previous = func_080094BC(9, 1);
        entry->current++;
        if (entry->current >= entry->count)
            entry->current = 0;
        selected = (u8)selected;
        if (func_08009030(selected, destination)) {
            entry = &(*current)->entries[9];
            func_080094BC(selected, 0);
            if (previous != func_080094BC(9, 1)) {
                entry->enabled = previous;
                if ((s16)control->field_1A > 2)
                    func_08008F94(6);
            }
            func_08141540(0x64);
        }
        return 0;
    }
    return func_0800927C(repeated);
}
