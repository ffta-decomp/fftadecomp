/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E35CC.c
 * Original SHA-256: 7b76475c64d02a8864db34158db8c39052759e736d4912569b0d08e876009baf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 value;
    u8 palette;
} UnitSettings;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    const UnitSettings *settings;
    u8 unknown_0C[8];
    s16 kind;
} EffectTask;

typedef struct {
    s16 x;
    s16 y;
    u16 delay;
    u8 special;
    u8 palette;
    u16 value;
    u8 unknown_0A[2];
    void *unit;
    void *startup;
    void *display;
    void *script;
    void *auxiliary;
    void *object;
    void *effect;
} EffectState;

typedef struct {
    u8 unknown_00[0x34];
    u16 value;
} UnitState;

extern const u8 data_0839612C[];
extern const u8 data_08396144[];
extern const u8 data_088F2BF0[];
extern const u8 data_0894D69C[];
extern const u8 data_0894CC1C[];
extern u16 g_control_flags_03000940;

extern void *func_080DD47C(void *object);
extern void func_080D38B4(void);
extern void *func_080D7A70(const void *data, u32 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void func_080DBDC8(void *unit, s16 *x, s16 *y);
extern void func_080D49FC(u8 kind, u8 mode, u16 option, s16 x, s16 y);
extern void *func_080D4B64(u8 kind, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080DFD8C(const void *data, u32 mode, u32 count, u32 option,
                          void *parent);
extern UnitState *func_080DD350(void *unit);
extern u8 func_080DBC18(void *unit, u8 palette);
extern void func_0809801C(UnitState *unit);
extern u32 func_080DD71C(void *unit);
extern void func_080DE10C(void *unit, u32 value);
extern void func_080DE390(void *unit);
extern void *func_080D3F08(void *script);
extern void *func_080D4D2C(void *display, u8 mode);
extern void *func_080D4774(void *auxiliary);

u32 func_080E35CC(void *object, EffectTask *task, EffectState *state)
{
    switch (task->state) {
    case 0:
        state->special = 0;
        if (task->kind == 0x167) {
            state->special = 1;
        } else {
            const UnitSettings *settings = task->settings;

            state->value = settings->value;
            state->palette = settings->palette;
        }
        state->object = task->object;
        state->unit = func_080DD47C(state->object);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->startup = func_080D7A70(data_0839612C, 2, object);
        task->state++;
        break;
    case 0x101:
        state->startup = func_080D7ABC(state->startup);
        if (state->startup)
            break;
        func_080DBDC8(state->unit, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->display = func_080D4B64(0, data_088F2BF0, 0x379, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->script = func_080D3E9C(data_0894D69C, object);
        state->auxiliary = func_080D4704(data_0894CC1C, object);
        state->effect = func_080DFD8C(data_08396144, 1, 4, 0, object);
        state->delay = 0x25;
        task->state++;
        break;
    case 0x102:
        if (state->delay) {
            state->delay--;
            if (state->delay)
                break;
            {
                UnitState *unit = func_080DD350(state->unit);
                u32 status;

                if (state->special == 0) {
                    unit->value = state->value;
                    func_080DBC18(state->unit, state->palette);
                } else {
                    func_0809801C(unit);
                }
                status = func_080DD71C(state->unit);
                if (status & 0x10)
                    func_080DE10C(state->unit, 0x14);
                else if (status & 8)
                    func_080DE10C(state->unit, 12);
                else
                    func_080DE390(state->unit);
            }
        }
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        state->display = func_080D4D2C(state->display, 0);
        if (state->display)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        state->auxiliary = func_080D4774(state->auxiliary);
        if (state->auxiliary == 0)
            task->state = 2;
        break;
    }
    return 0;
}
