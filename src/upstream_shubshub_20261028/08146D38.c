/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08146D38.c
 * Original SHA-256: aa3fc20feb962afd5893a65a56925d6d72db67ec707d4eaaea75759c2533b454
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct
{
    u16 remaining;
    u16 frame;
    u16 frame_count;
    u16 unknown_06;
    const u16 *const *frames;
    const u16 *durations;
} PaletteSequence;

typedef struct
{
    u16 active;
    u16 flags;
    u16 unknown_04;
    u16 first_color;
    u16 last_color;
    u16 unknown_0A;
    PaletteSequence sequence;
} PaletteAnimation;

extern u16 data_03003860[];

/* Complete target: 0x08146D38..0x08146DC8, 144 bytes. */
void func_08146D38(PaletteAnimation *animation)
{
    u32 finished = 0;
    PaletteSequence *sequence = &animation->sequence;

    sequence->remaining--;
    if (sequence->remaining == 0)
    {
        const u16 *colors = sequence->frames[sequence->frame];
        u16 destination = animation->first_color;
        u16 index = 0;

        for (; destination <= animation->last_color; destination++, index++)
            data_03003860[destination] = colors[index];

        sequence->frame++;
        if (sequence->frame >= sequence->frame_count)
        {
            sequence->frame = 0;
            if (!(animation->flags & 4))
                finished = 1;
        }
        sequence->remaining = sequence->durations[sequence->frame];
    }
    if (finished)
        animation->active = 0;
}
