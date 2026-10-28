/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08120DF0.c
 * Original SHA-256: 57ea6cd778085dd0cf7caa3507047c2ca6e19a91fc88e42a50898cd19f7f3cdb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
} EffectCommand;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    void *entity;
    void *child;
    void *script;
    void *object;
} EffectState;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;

extern void *func_080DD4A4(void *object, u32 mode);
extern void *func_080DD748(void *unit, s16 *x, s16 *y, u32 mode);
extern void *func_080D3508(u16 identifier, void *object, void *entity);
extern void *func_080DF8E8(void *entity, u32 mode, u32 flags, void *parent);
extern void *func_080DF90C(void *entity, u32 mode, void *parent);
extern void *func_080DBA5C(void *child);
extern void *func_080D3888(void *script);

/* Complete [0x08120DF0, 0x08120FB6): 454 bytes, 185 instructions. */
u32 func_08120DF0(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        break;
    case 1:
        break;
    case 0x100: {
        void *unit = func_080DD4A4(state->object, 0);

        state->entity = func_080DD748(unit, &state->x, &state->y, 0);
        command->state++;
        break;
    }
    case 0x101:
        if (data_03000000.pressed & 8) {
            command->state = 0x104;
        } else if (data_03000000.pressed & 1) {
            state->script = func_080D3508(0x161, state->object, state->entity);
            command->state = 0x103;
        } else if (data_03000000.pressed & 0x200) {
            state->script = func_080D3508(0x164, state->object, state->entity);
            command->state = 0x103;
        } else if (data_03000000.pressed & 0x100) {
            state->script = func_080D3508(0x165, state->object, state->entity);
            command->state = 0x103;
        } else if (data_03000000.pressed & 4) {
            state->script = func_080D3508(0x163, state->object, state->entity);
            command->state = 0x103;
        } else if (data_03000000.pressed & 2) {
            state->child = func_080DF8E8(state->entity, 0, 0, context);
            command->state++;
        }
        break;
    case 0x102:
        if (data_03000000.pressed & 8) {
            command->state = 0x104;
        } else {
            state->child = func_080DBA5C(state->child);
            if (state->child == 0 && (data_03000000.pressed & 2)) {
                state->child = func_080DF90C(state->entity, 0, context);
                command->state++;
            }
        }
        break;
    case 0x103:
        if (data_03000000.pressed & 8) {
            command->state = 0x104;
        } else {
            state->child = func_080DBA5C(state->child);
            if (state->child == 0)
                command->state = 0x101;
        }
        break;
    case 0x104:
        state->child = func_080DBA5C(state->child);
        if (state->child == 0)
            command->state = 2;
        break;
    case 0x105:
        state->child = func_080DBA5C(state->child);
        if (state->child)
            break;
        state->script = func_080D3888(state->script);
        if (state->script == 0)
            command->state = 2;
        break;
    }
    return 0;
}
