/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802158C.c
 * Original SHA-256: 06dfcfd1efac03ee4b55550d539aa93a40892025b28c8bd82daaa7d3517590bd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[20];
} ResourceFrame;

typedef struct {
    u16 length;
    u16 unknown_02;
    ResourceFrame frames[0];
} Resource;

typedef struct {
    u32 flags;
    u16 unknown_04;
    u16 category;
    u16 selector;
    u16 position;
    s16 frame;
    u16 limit;
    u8 active;
    u8 unknown_11[0x0F];
    s32 counter;
    u8 unknown_24[0x10];
    const ResourceFrame *start;
    const ResourceFrame *cursor;
    u8 unknown_3C[0x0C];
} ResourceState;

extern ResourceState data_0200F1D8;
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);
extern const u8 *func_08021004(u32 category, u32 selector);

/* 0x0802158C: 140 bytes; change a resource while retaining its cursor state. */
void func_0802158C(ResourceState *state, u32 category, u32 selector, u32 index)
{
    const Resource *const *resources =
        (const Resource *const *)func_08021004(category, selector);
    const Resource *resource;
    const ResourceFrame *frames;
    u32 flags;
    s32 variant;

    data_0836D4BC(&data_0200F1D8, state, sizeof(*state));
    resource = resources[index];
    flags = 0x45;
    state->position = 0;
    state->frame = 0;
    state->limit = resource->length;
    frames = resource->frames;
    state->start = frames;
    state->counter = -1;
    state->cursor = frames + data_0200F1D8.frame;
    state->position = data_0200F1D8.position;
    state->active = data_0200F1D8.active;
    state->category = category;
    state->selector = selector;
    state->flags = flags;

    variant = selector & 3;
    switch (variant) {
    case 2:
    case 3:
        state->flags = 0x65;
        break;
    }
}
