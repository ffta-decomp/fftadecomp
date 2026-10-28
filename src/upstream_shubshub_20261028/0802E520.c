/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802E520.c
 * Original SHA-256: 8129a73e9798de30efde605797233bb4a0582862d5babb96bc07af30bb5552c6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 x;
    u8 unknown_01;
    u8 y;
    u8 unknown_03[5];
    u8 height;
    u8 unknown_09[0x465 - 9];
    u8 initial;
    u8 progress;
    u8 unknown_467[0x7DC - 0x467];
    u16 tiles[26];
} BorderState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} BorderMap;

extern BorderState *data_0200F444;
extern BorderMap data_03000990;
extern BorderMap data_030008B0;

void *func_0802DFCC(void);
u16 func_080161A0(u8 x, u8 y, u8 width);
void func_08000A98(void *request, const void *source, void *destination,
                   u16 count);
void func_08000BAC(void *request, const void *source, void *destination,
                   u16 width, u16 height, u16 source_stride,
                   u16 destination_stride);

/* Complete target: [0x0802E520, 0x0802E68C), 364 bytes. */
u32 func_0802E520(void)
{
    if (data_0200F444->progress != 0) {
        u8 y = data_0200F444->y + 2;
        const u16 *source = data_0200F444->tiles;
        u16 *destination;

        destination = data_03000990.map +
            func_080161A0(data_0200F444->x,
                          y + data_0200F444->height * 2, 32);
        if (data_0200F444->progress == data_0200F444->initial)
            func_08000A98(func_0802DFCC(), source, destination, 26);

        destination = data_03000990.map +
            func_080161A0(data_0200F444->x,
                          y + (data_0200F444->progress - 1) * 2, 32);
        func_08000BAC(func_0802DFCC(), source, destination, 26, 2, 52, 64);

        destination = data_030008B0.map +
            func_080161A0(data_0200F444->x + 1,
                          y + (data_0200F444->progress - 1) * 2, 32);
        func_08000BAC(func_0802DFCC(), source, destination, 26, 2, 52, 64);
    }

    data_0200F444->progress--;
    if (data_0200F444->progress == 0) {
        void *request = func_0802DFCC();
        u16 *destination = data_03000990.map +
            func_080161A0(data_0200F444->x, data_0200F444->y, 32);

        func_08000BAC(request, data_0200F444->tiles,
                       destination, 26, 2, 52, 64);
    }
    return data_0200F444->progress == 0;
}
