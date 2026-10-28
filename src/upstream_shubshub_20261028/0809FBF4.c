/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809FBF4.c
 * Original SHA-256: 0ae1bc4d536286f49b233b6f8c1df1bc375e149ce41413338f408fd0868c1c73
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0809FBF4..0x0809FD26: 306 bytes. */
typedef struct {
    u8 flags;
    s8 x;
    s16 y;
} PathPoint;

typedef struct {
    s16 x;
    s16 y;
} OutputPoint;

u32 func_0809FBF4(PathPoint *path, s32 length, s32 scale_x, s32 scale_y,
                   s8 *offsets, OutputPoint *output)
{
    u32 count;
    s32 index;

    if (output != 0) {
        output[0].x = path[0].x * scale_x;
        output[0].y = path[0].y * scale_y;
        output[1].x = path[0].x * scale_x;
        output[1].y = (path[0].y + offsets[0]) * scale_y;
    }

    count = 2;
    for (index = 1; index < length - 1; ++index) {
        if (path[index].flags & 1) {
            if (output != 0) {
                output[count].x = (path[index].x - 1) * scale_x;
                output[count].y = (path[index].y + offsets[0]) * scale_y;
            }
            ++count;
        }

        if (output != 0) {
            output[count].x = path[index].x * scale_x;
            output[count].y = (path[index].y + offsets[1]) * scale_y;
        }
        ++count;

        if (path[index].flags & 2) {
            if (output != 0) {
                output[count].x = (path[index].x + 1) * scale_x;
                output[count].y = (path[index].y + offsets[2]) * scale_y;
            }
            ++count;
        }
    }

    if (output != 0) {
        output[count].x = path[index].x * scale_x;
        output[count].y = (path[index].y + offsets[0]) * scale_y;
        output[count + 1].x = path[index].x * scale_x;
        output[count + 1].y = path[index].y * scale_y;
    }
    count += 2;
    return count;
}
