/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020E3C.c
 * Original SHA-256: ec02e8aae0c19074d484f18e654479616b5f71a6076fdfde7d22308d7032723d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08020E3C .. 08020F34: 248 bytes. */
typedef struct {
    u8 duration_low;
    u8 duration_high;
    u8 offset_low;
    u8 offset_high;
} AnimationFrame;

typedef struct {
    u8 width;
    u8 height;
    u8 unknown_02[2];
    AnimationFrame frames[1];
} AnimationResource;

typedef struct {
    u8 active;
    u8 enabled;
    u16 duration;
    u8 frame;
    u8 flags;
    u16 unknown_06;
    u16 size;
    u16 start_tick;
    u16 elapsed;
    u16 unknown_0E;
    const AnimationResource *resource;
    u16 *destination;
    const u16 *data;
    u16 *position;
    const u16 *end;
    u8 layer;
    u8 dimensions[2];
    u8 x;
    u8 y;
    u8 unknown_29[3];
} AnimationSlot;

typedef struct {
    u16 tick;
    u16 unknown_02;
    AnimationSlot slots[4];
} AnimationState;

extern AnimationState *g_state_0200F1D4;
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u16 *func_0801AD1C(u8);

static inline AnimationSlot *find_free_slot(void)
{
    u8 index;
    for (index = 0; index < 4; index++) {
        if (g_state_0200F1D4->slots[index].active == 0)
            return &g_state_0200F1D4->slots[index];
    }
    return 0;
}

AnimationSlot *func_08020E3C(const AnimationResource *resource,
                           u8 layer, u8 x, u8 y, const u16 *data)
{
    AnimationSlot *slot = find_free_slot();
    u16 *base;

    g_callbacks_0836D4B8[0](slot, sizeof(AnimationSlot));
    slot->enabled = 1;
    {
        u32 low = resource->frames[slot->frame].duration_low;
        u32 high = resource->frames[slot->frame].duration_high;
        slot->duration = (high << 8) | low;
    }
    slot->frame = 0;
    slot->flags = 0xFF;
    base = func_0801AD1C(layer);
    slot->size = (resource->width << 1) * resource->height;
    slot->start_tick = g_state_0200F1D4->tick;
    slot->elapsed = 0;
    slot->resource = resource;
    slot->destination = base + (y * 64 + x);
    slot->data = data;
    slot->position = slot->destination;
    {
        u32 low = resource->frames[slot->frame].offset_low;
        u32 high = resource->frames[slot->frame].offset_high;
        slot->end = data + ((high << 8) | low);
    }
    slot->layer = layer;
    slot->dimensions[0] = resource->width;
    slot->dimensions[1] = resource->height;
    slot->x = x;
    slot->y = y;
    slot->active = 1;
    return slot;
}
