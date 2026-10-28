/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021CB0.c
 * Original SHA-256: fa572159b8cb5f478118872f11fb339d916ff79b0700031beecbde5ad4fed5cd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Resource {
    u16 length;
    u16 unknown_02;
    u8 data[1];
} Resource;

typedef struct ResourceState {
    u32 flags;
    u16 unknown_04;
    u16 category;
    u16 selector;
    u16 position;
    u16 frame;
    u16 limit;
    u8 active;
    u8 unknown_11[0x0f];
    s32 counter;
    u8 unknown_24[0x10];
    const u8 *start;
    const u8 *cursor;
} ResourceState;

extern const u8 *func_08021004(u32 category, u32 selector);

/* 08021CB0..08021D0A: 90 bytes, 44 instructions. */
u32 func_08021CB0(ResourceState *state, u32 category, u32 selector, u32 index)
{
    const Resource *const *resources =
        (const Resource *const *)func_08021004(category, selector);
    const Resource *resource = resources[index];
    s32 variant;

    if (resource == 0)
        return 0;

    state->flags = 0x45;
    state->position = 0;
    state->frame = 0;
    state->limit = resource->length;
    state->start = resource->data;
    state->cursor = resource->data;
    state->counter = -1;
    state->active = 0;
    state->category = category;
    state->selector = selector;

    variant = selector & 3;
    switch (variant) {
    case 2:
    case 3:
        state->flags = 0x65;
        break;
    }
    return 1;
}
