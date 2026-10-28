/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809AEF8.c
 * Original SHA-256: 552c2801eb6afc928b3a72fc9d30b41cbf9da11985d5d8d9bbed71131da4fd1d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0809AEF8 .. 0809B014: 284 bytes. */
typedef struct {
    s16 x;
    s16 y;
} Point;

typedef struct {
    u8 flags;
    s8 x;
    s16 y;
} PathPoint;

typedef struct {
    u8 unknown_00[2];
    u8 index;
    u8 unknown_03;
} PathInput;

typedef struct {
    double *horizontal;
    double *vertical;
    s32 count;
    u8 phase;
} BoundaryState;

typedef struct {
    Point points[32];
    PathPoint path[32];
    u16 indices[32];
    s16 path_count;
    s16 point_count;
    s16 steps;
    u16 unknown_146;
    BoundaryState boundary;
    u8 unknown_158[0x10C];
    double horizontal[32];
    double vertical[32];
    u8 unknown_464[0x1018];
    s32 origin_x;
    s32 origin_y;
} PathState;

extern s8 data_08394354[];
extern s32 func_0809FA1C(u16 *indices, s32 count, PathPoint *path);
extern u32 func_0809FBF4(PathPoint *path, s32 length, s32 scale_x,
                         s32 scale_y, s8 *offsets, Point *output);
extern s32 func_08007B70(BoundaryState *state, double *horizontal,
                         double *vertical, s32 count);

void func_0809AEF8(PathState *state, PathInput *input, s32 count)
{
    s32 index;

    for (index = 0; index < count; ++index, ++input)
        state->indices[index] = input->index;
    state->path_count = func_0809FA1C(state->indices, count, state->path);
    state->point_count = func_0809FBF4(state->path, state->path_count, 32, 16,
                                    data_08394354, state->points);
    state->origin_x = state->points[0].x;
    state->origin_y = state->points[0].y;
    for (index = 0; index < state->point_count; ++index) {
        state->horizontal[index + 2] =
            (double)(state->points[index].x - state->origin_x);
        state->vertical[index + 2] =
            (double)(state->points[index].y - state->origin_y);
    }
    state->steps = func_08007B70(&state->boundary, state->horizontal,
                               state->vertical, state->point_count);
}
