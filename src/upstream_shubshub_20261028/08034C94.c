/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08034C94.c
 * Original SHA-256: f2e41bccd79d0bcd9650f6020cd8410a37e18309e6b864e1e9e36485ea46abba
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 mode : 3;
    u8 active : 1;
    u8 next : 3;
    u8 unknown : 1;
} __attribute__((packed)) AnimationFlags;

typedef struct {
    u8 unknown_00[0x9A];
    AnimationFlags first;
    u8 unknown_9B[0x32];
    s8 first_position;
    u8 unknown_CE[0x18];
    AnimationFlags second;
    u8 unknown_E7[0x32];
    s8 second_position;
} AnimationState;

typedef struct {
    u8 flags;
    u8 unknown_01[0x17];
    s8 position;
} SlidingObject;

typedef struct {
    u32 unknown_00;
    SlidingObject *object;
} SlidingState;

extern AnimationState data_030009E0;
extern SlidingState *g_state_03002810;
extern void func_0808A604(u32 object, u32 animation);

/* Complete target: [0x08034C94, 0x08034E34), 416 bytes. */
void func_08034C94(void)
{
    SlidingObject *object;

    if (data_030009E0.first.active)
    {
        if (data_030009E0.first.mode == 5)
        {
            if (data_030009E0.first_position > 17)
            {
                data_030009E0.first_position--;
                func_0808A604(2, 8);
            }
            else
            {
                data_030009E0.first.active = 0;
                data_030009E0.first.next = 5;
                data_030009E0.first.mode = 0;
            }
        }
        else if (data_030009E0.first.mode == 6)
        {
            if (data_030009E0.first_position <= 20)
            {
                data_030009E0.first_position++;
                func_0808A604(2, 8);
            }
            else
            {
                data_030009E0.first.active = 0;
                data_030009E0.first.next = 6;
                data_030009E0.first.mode = 0;
            }
        }
    }
    else
    {
        switch (data_030009E0.first.mode)
        {
        case 0:
            break;
        case 5:
            data_030009E0.first.active = 1;
            break;
        case 6:
            data_030009E0.first.active = 1;
            break;
        case 7:
            data_030009E0.first_position = 20;
            func_0808A604(2, 8);
            data_030009E0.first.active = 0;
            data_030009E0.first.next = 6;
            data_030009E0.first.mode = 0;
            break;
        }
    }

    if (data_030009E0.second.active)
    {
        if (data_030009E0.second.mode == 5)
        {
            if (data_030009E0.second_position > 18)
            {
                data_030009E0.second_position--;
                func_0808A604(3, 8);
            }
            else
            {
                data_030009E0.second.active = 0;
                data_030009E0.second.next = 5;
                data_030009E0.second.mode = 0;
            }
        }
        else if (data_030009E0.second.mode == 6)
        {
            if (data_030009E0.second_position <= 22)
            {
                data_030009E0.second_position++;
                func_0808A604(3, 8);
            }
            else
            {
                data_030009E0.second.active = 0;
                data_030009E0.second.next = 6;
                data_030009E0.second.mode = 0;
            }
        }
    }
    else
    {
        switch (data_030009E0.second.mode)
        {
        case 0:
            break;
        case 5:
            data_030009E0.second.active = 1;
            break;
        case 6:
            data_030009E0.second.active = 1;
            break;
        case 7:
            data_030009E0.second_position = 22;
            func_0808A604(3, 8);
            data_030009E0.second.active = 0;
            data_030009E0.second.next = 6;
            data_030009E0.second.mode = 0;
            break;
        }
    }

    object = g_state_03002810->object;
    if (object->flags & 0x20)
    {
        if (object->position <= 23)
            object->position += 2;
    }
    else
    {
        if (object->position > 0)
            object->position -= 2;
    }
}
