/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808748C.c
 * Original SHA-256: 22ba15013d5e8cfb56cca3330db5339b444c2f2412bbf59c6b53ddbaa5612da6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
} TilePoint;

typedef struct {
    s8 x;
    s8 y;
    s8 width;
    s8 height;
} TileRect;

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
} TileBuffer;

void func_0808748C(TileBuffer *source, TileBuffer *destination,
                   TilePoint origin, TileRect rectangle)
{
    s32 row;
    s32 column;

    for (row = 0; row < rectangle.height; row++) {
        u16 *source_first = source->first_plane + origin.x
            + (origin.y + row) * source->stride;
        u16 *source_second = source->second_plane + origin.x
            + (origin.y + row) * source->stride;
        u16 *destination_first = destination->first_plane + rectangle.x
            + (rectangle.y + row) * destination->stride;
        u16 *destination_second = destination->second_plane + rectangle.x
            + (rectangle.y + row) * destination->stride;

        for (column = 0; column < rectangle.width; column++) {
            destination_first[column] = source_first[column];
            destination_second[column] = source_second[column];
        }
    }
}
