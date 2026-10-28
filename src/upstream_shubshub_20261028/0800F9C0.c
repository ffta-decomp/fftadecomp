/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800F9C0.c
 * Original SHA-256: 5ccb4d06a053874d4dd30b1c7c3932059d437fc2bd2dcee592cad068997eee39
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800F9C0..0x0800FA0C: 76 bytes. */

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    u16 count;
    u16 frames[1][4];
} PositionedAnimation;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    s32 *shapes;
    PositionedAnimation *animation;
    u16 frame;
    u16 remaining;
    u16 frameCount;
} AnimatedScanlines;

typedef struct ScanlineTask ScanlineTask;

extern void func_0800F93C(AnimatedScanlines *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(
    void (*callback)(AnimatedScanlines *, u16 *), u32 size, u32 type,
    u16 *destination);
extern AnimatedScanlines *func_0800C614(ScanlineTask *task);
extern u16 data_04000040[];

ScanlineTask *func_0800F9C0(u8 window, u8 left, u8 right)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C,
                                    sizeof(AnimatedScanlines), 2,
                                    data_04000040 + window);
    AnimatedScanlines *state = func_0800C614(task);
    Scanline *line;
    s32 remaining;

    state->type = 0;
    line = state->lines;
    for (remaining = 159; remaining >= 0; remaining--) {
        line->left = left;
        line->right = right;
        line++;
    }
    return task;
}
