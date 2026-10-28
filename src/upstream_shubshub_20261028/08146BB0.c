/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08146BB0.c
 * Original SHA-256: f5e9a089bee4f02dbd46d24f049a39831e61a818be224acc3237533629dd0f99
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08146BB0, 0x08146C8C), 220 bytes. */
typedef struct {
    u16 interval_index;
    u16 interval_count;
    const u16 *intervals;
    u16 length;
    u16 remaining;
    u16 fixed_interval;
    u16 timer;
    const u8 *colors;
    u16 color_offset;
} Rotation;

typedef struct {
    u16 active;
    u16 flags;
    u16 unknown_04;
    u16 first;
    u16 last;
    u16 unknown_0A;
    Rotation rotation;
} PaletteEffect;

extern u16 data_03003860[];

void func_08146BB0(PaletteEffect *effect)
{
    Rotation *rotation = &effect->rotation;
    const u8 *colors = rotation->colors;
    u16 color = *(const u16 *)(colors + rotation->color_offset);

    if (--rotation->timer == 0) {
        u16 index;
        u16 insertion;

        if (effect->flags & 2) {
            for (index = effect->last; index >= effect->first; index--)
                data_03003860[index] = data_03003860[index - 1];
            insertion = effect->first;
        } else {
            for (index = effect->first; index <= effect->last; index++)
                data_03003860[index] = data_03003860[index + 1];
            insertion = effect->last;
        }
        data_03003860[insertion] = color;
        rotation->color_offset += 2;

        if (rotation->fixed_interval == 0) {
            rotation->interval_index++;
            if (rotation->interval_index >= rotation->interval_count)
                rotation->interval_index = 0;
            rotation->timer = rotation->intervals[rotation->interval_index];
        } else {
            rotation->timer = rotation->fixed_interval;
        }
        rotation->remaining--;
    }

    if (rotation->remaining == 0) {
        u16 repeat = effect->flags & 4;

        if (repeat) {
            rotation->remaining = rotation->length;
            rotation->color_offset = 0;
        } else {
            effect->active = 0;
        }
    }
}
