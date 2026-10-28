/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800FF00.c
 * Original SHA-256: 5b9ded510ea09072304d38e4b6ecafb5508cc96cb8bd768b648016eb7b19c328
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800FF00..0x0800FF68: 104 bytes. */

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    u16 count;
    /* Each frame contains shape, duration, x and y halfwords. */
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
extern void func_0800C628(ScanlineTask *task, u8 enabled);
extern u16 data_04000040[];

ScanlineTask *func_0800FF00(u8 window, s32 *shapes,
                          PositionedAnimation *animation)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C,
                                    sizeof(AnimatedScanlines), 2,
                                    data_04000040 + window);
    AnimatedScanlines *state = func_0800C614(task);

    state->type = 10;
    state->shapes = shapes;
    state->animation = animation;
    state->frame = 0;
    state->frameCount = animation->count;
    state->remaining = animation->frames[0][1];
    func_0800C628(task, 1);
    return task;
}
