/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BE494.c
 * Original SHA-256: 692158a0cf92f426bf5ec88bf3e2c4cfca49eeaed3c7c2b193615a8fa4d7a599
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Actor080BE494 {
    u8 unknown00[0xF6];
    u8 x;
    u8 y;
};

struct Unit080BE494 {
    struct Actor080BE494 *actor;
};

struct Action080BE494 {
    u16 action;
    u8 unknown02[10];
    s16 value;
    u8 unknown0E[3];
    u8 flags;
    u8 unknown12[2];
};

struct Entry080BE494 {
    struct Unit080BE494 *unit;
    struct Action080BE494 actions[40];
    u16 count;
    u8 unknown326[2];
};

struct Group080BE494 {
    struct Entry080BE494 entries[13];
    u16 count;
};

struct Context080BE494 {
    struct Unit080BE494 *unit;
    u8 unknown04[4];
    u16 action;
    u8 unknown0A[2];
    struct Group080BE494 *groups[2];
    u8 unknown14[6];
    u16 parameter;
    u8 unknown1C[12];
    u8 invert;
};

struct Position080BE494 {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown03;
};

extern s16 func_080BDECC(struct Unit080BE494 *source,
                        struct Unit080BE494 *target,
                        u16 action, u16 parameter);

static inline struct Entry080BE494 *find_position(struct Group080BE494 *group,
                                                  u8 x, u8 y)
{
    s32 i;

    for (i = 0; i < group->count; i++) {
        if (group->entries[i].unit->actor->x == x &&
            group->entries[i].unit->actor->y == y)
            return &group->entries[i];
    }
    return 0;
}

static inline struct Action080BE494 *find_action(struct Entry080BE494 *entry,
                                                 u16 action)
{
    s32 i;

    for (i = 0; i < entry->count; i++) {
        if (entry->actions[i].action == action)
            return &entry->actions[i];
    }
    return 0;
}

/* Complete [0x080BE494, 0x080BE5F4): 352 bytes, 173 instructions. */
s32 func_080BE494(struct Context080BE494 *context,
                  const struct Position080BE494 *positions, s32 count)
{
    s32 side;
    s32 i;
    struct Group080BE494 *group;
    s32 accepted = 0;

    for (side = 0; side < 2; side++) {
        group = context->groups[side];

        for (i = 0; i < count; i++) {
            struct Entry080BE494 *entry = find_position(group, positions[i].x,
                                                        positions[i].y);

            if (entry && entry->unit != context->unit) {
                struct Action080BE494 *record = find_action(entry, context->action);

                if (record->value != 0) {
                    s32 value = func_080BDECC(context->unit, entry->unit,
                                             context->action, context->parameter);

                    if (value < 0)
                        value = -value;
                    if (record->value < 0)
                        value *= -100;
                    if (!(record->flags & 1)) {
                        if (context->invert)
                            value = -value;
                        if (side)
                            value = -value;
                        if (value < 0)
                            return -1;
                        accepted++;
                    }
                }
            }
        }
    }
    return accepted;
}
