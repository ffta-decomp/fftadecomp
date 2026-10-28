/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A54E0.c
 * Original SHA-256: 7467b81651a5217af22db37ea41761426392d1a928a5e32e0200e79305c8b864
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF8];
    s8 value;
} UnitValue;

typedef struct {
    UnitValue *unit;
    u8 unknown_04[0x1B];
    s8 value;
    u8 unknown_20[0x10];
    u32 flags;
} ObjectValue;

typedef struct {
    ObjectValue *object;
    u8 unknown_04[0x0A];
    u16 type;
    u32 flags;
    u8 unknown_14[0x18];
} EntryValue;

typedef struct {
    ObjectValue *primary;
    u8 unknown_04[4];
    s8 value;
    u8 unknown_09[7];
    u16 enabled;
    u8 unknown_12[0x0E];
    EntryValue entries[15];
    u8 unknown_2B4[0x0C];
    u8 count;
} UpdateState;

extern void func_0809836C(ObjectValue *object, u32 selector,
                          s32 value, u32 mode);

/* 0x080A54E0..0x080A5580: 160 bytes. */
void func_080A54E0(UpdateState *state)
{
    s32 i;

    if (state->primary != 0) {
        func_0809836C(state->primary, 10, state->value, 0);
        state->primary->unit->value = state->value;
    }
    for (i = 0; i < state->count; i++) {
        if (state->entries[i].type == 1 || state->entries[i].type == 2 ||
            state->entries[i].type == 5 || state->enabled != 0)
            func_0809836C(state->entries[i].object, 10,
                           state->entries[i].object->value, 0);
        if (state->entries[i].flags & 0x800)
            state->entries[i].object->flags |= 1;
    }
}
