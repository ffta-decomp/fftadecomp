/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802E890.c
 * Original SHA-256: 247829aba23954dd66dbc4dc7cea23f3b8c93a6312c97140b54336ccd27d46a0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 x;
    u8 unknown_01;
    u8 y;
    u8 unknown_03[2];
    u8 mode;
    u8 unknown_06[2];
    u8 height;
    u8 unknown_09[2];
    u8 step;
} BorderState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} BorderMap;

extern BorderState *data_0200F444;
extern const u16 data_083C4AD8[];
extern BorderMap data_03000990;
extern BorderMap data_030008B0;
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern void func_0802EB58(void);

/* Complete target: [0x0802E890, 0x0802EAE0), 592 bytes. */
u32 func_0802E890(void)
{
    u32 finished = 0;
    u16 offset = 24 - data_0200F444->step * 2;
    const u16 *source;
    u16 index;
    u16 *destination;
    s32 i;

    if (data_0200F444->step == 5)
        finished = 1;
    source = data_083C4AD8;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + offset, data_0200F444->y, 32);
    destination[0] = 0;
    destination[1] = 0;
    destination -= 2;
    if (finished)
    {
        destination[0] = (source[0] & 0x0FFF) + 0x7000;
        destination[1] = (source[1] & 0x0FFF) + 0x7000;
    }
    else
    {
        destination[0] = source[0];
        destination[1] = source[1];
    }

    source += 26;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + offset, data_0200F444->y + 1, 32);
    destination[0] = 0;
    destination[1] = 0;
    destination -= 2;
    if (finished)
    {
        destination[-1] = source[-14];
        destination[0] = source[-14];
        destination[1] = (source[1] & 0x0FFF) + 0x7000;
    }
    else
    {
        destination[0] = source[0];
        destination[1] = source[1];
    }

    source += 26;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + offset,
                      data_0200F444->height * 2 + data_0200F444->y + 2, 32);
    destination[0] = 0;
    destination[1] = 0;
    destination -= 2;
    if (finished)
    {
        destination[0] = (source[0] & 0x0FFF) + 0x7000;
        destination[1] = (source[1] & 0x0FFF) + 0x7000;
    }
    else
    {
        destination[0] = source[0];
        destination[1] = source[1];
    }

    source += 26;
    for (i = 0; i < data_0200F444->height; i++)
    {
        u16 *background;
        u16 *background_left;
        u16 *lower;

        index = func_080161A0(data_0200F444->x + offset,
                             i * 2 + 2 + data_0200F444->y, 32);
        destination = data_03000990.map + index;
        background = data_030008B0.map + index;
        background_left = background - 2;
        background_left[0] = 0;
        destination[0] = 0;
        background_left[1] = 0;
        destination[1] = 0;
        lower = destination + 32;
        background[30] = 0;
        lower[0] = 0;
        lower++;
        background[31] = 0;
        lower[0] = 0;
        destination -= 2;
        if (finished)
        {
            destination[0] = (source[0] & 0x0FFF) + 0x7000;
            destination[1] = (source[1] & 0x0FFF) + 0x7000;
            destination[32] = (source[26] & 0x0FFF) + 0x7000;
            destination[33] = (source[27] & 0x0FFF) + 0x7000;
        }
        else
        {
            destination[0] = source[0];
            destination[1] = source[1];
            destination[32] = source[26];
            destination[33] = source[27];
        }
    }

    data_0200F444->step++;
    if (data_0200F444->mode == 12)
        func_0802EB58();
    return finished;
}
