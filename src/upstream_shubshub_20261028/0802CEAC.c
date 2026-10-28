/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802CEAC.c
 * Original SHA-256: 4594e92d62dfa38fec5dd3c623156b047eb000108cadc17e3950e1b358a79294
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 row;
    u8 unknown_08[0x0B];
    u8 shift;
    u8 unknown_14[0x14];
    u16 first[6][17];
    u8 unknown_F4[0x34];
    u16 second[7][17];
    u8 unknown_216[0x112];
    u16 second_source[7][17];
    u8 unknown_416[0x12];
    u16 first_source[6][17];
} TileRows;

typedef struct {
    u8 unknown_00[0x14];
    u8 *map;
} TileMap;

extern TileMap data_03000990;
extern TileMap data_030008B0;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void *func_0802BA08(void);
extern void func_08000BAC(void *request, const void *source, void *destination,
                         u16 width, u16 height, u16 source_stride, u16 destination_stride);

/* Complete target: [0x0802CEAC, 0x0802CFB0), 260 bytes. */
void func_0802CEAC(TileRows *state)
{
    u16 *destination = state->first[0];
    const u16 *source = state->first_source[0];
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++)
    {
        func_0814186C(source + state->shift, destination,
                      (17 - state->shift) & 0x1FFFFF);
        for (j = 17 - state->shift; j < 17; j++)
            destination[j] = 0;
        destination += 17;
        source += 17;
    }
    func_08000BAC(func_0802BA08(), state->first,
                  data_03000990.map + state->row * 64, 17, 6, 34, 64);

    destination = state->second[0];
    source = state->second_source[0];
    for (i = 0; i <= 6; i++)
    {
        func_0814186C(source + state->shift, destination,
                      (17 - state->shift) & 0x1FFFFF);
        for (j = 17 - state->shift; j < 17; j++)
            destination[j] = 0;
        destination += 17;
        source += 17;
    }
    func_08000BAC(func_0802BA08(), state->second,
                  data_030008B0.map + state->row * 64, 17, 7, 34, 64);
}
