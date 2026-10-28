/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F2FFC.c
 * Original SHA-256: cd99c4972c75f2e84d1ef75430f023c6da38085486801e14aa9b771dd2ff4b46
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete 0x080F2FFC..0x080F33A2: 934 bytes, 395 instructions. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u32 unknown_10;
    s16 effect;
    u16 variant;
} EffectCommand;

typedef struct {
    u16 unknown_00;
    u16 animation;
    u16 palette;
    u8 unknown_06[3];
    u8 mode;
    u8 unknown_0a[10];
} EffectConfig;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 timer;
    u8 alternate;
    u8 kind;
    u8 variant;
    u8 ready;
    u32 unknown_0c;
    void *output;
    void *position_source;
    void *actor;
    void *opening;
    void *particles[3];
    void *timeline;
    void *actor_effect;
    void *preparation;
    EffectConfig config;
    void *script;
} EffectState;

typedef void (*BufferCopier)(void *, const void *, u32);
extern BufferCopier data_0836D4BC;
extern const u8 data_0839AA30[];
extern const void *data_0839AA48[];
extern const u8 data_0839AA68[];
extern const void *data_0839AA70[];
extern const EffectConfig data_0839AA90;
extern const u16 data_0839AAA4[];
extern const u8 data_0839AAB4[];
extern const u8 data_0839AABC[];
extern const u8 data_0839AAC4[];
extern const u8 data_0839AACC[];
extern const u8 data_084F6130[];
extern const u8 data_084FF2AC[];

extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void func_080DBFFC(void *, u32);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u8);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD73C(void *);
extern void *func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08011058(void *, s16);
extern void *func_080D4704(const void *, void *);
extern u8 func_080DD670(void *, u8);
extern u8 func_080DD5EC(void *);
extern void *func_080DCFE4(void *, const EffectConfig *, u8, u16, u16,
                          void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D5F24(void **, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_080F2FFC(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->phase) {
    case 0:
        {
            u32 mode;

            switch (command->effect) {
            case 75:
                state->kind = 0;
                break;
            case 76:
                state->kind = 1;
                break;
            case 77:
                state->kind = 2;
                break;
            case 78:
                state->kind = 3;
                break;
            case 120:
                state->kind = 4;
                break;
            case 138:
                state->kind = 5;
                break;
            case 142:
                state->kind = 6;
                break;
            case 289:
                state->kind = 7;
                break;
            }
            state->variant = command->variant;
            state->actor = command->actor;
            mode = 2;
            if (state->variant)
                mode = 0;
            if (command->flags & 2)
                state->alternate = 1;
            state->opening = func_080E03F8(state->actor, data_0839AA30,
                                           mode, 0, 0, context);
            func_080D45D0(data_0839AA48[state->kind], 6, 1,
                          data_0839AA68[state->kind], 1);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->opening = func_080E05DC(state->opening);
        if (state->opening == 0) {
            if (func_080D3B54(state->actor)) {
                command->phase = 2;
            } else {
                u16 flags = 0x8007;

                if (state->kind == 7) {
                    flags = 0x54;
                    if (state->alternate)
                        flags = 0x34;
                }
                state->preparation = func_080DDF68(state->actor,
                    &state->output, flags, 2, &state->ready,
                    data_0839AABC, 13, 0, context);
                command->phase++;
            }
        }
        break;
    case 0x101:
        if (state->ready) {
            state->timer = 10;
            command->phase++;
        }
        break;
    case 0x102:
        state->timer--;
        if (state->timer != 0)
            break;
        func_080DBFFC(state->actor, 0);
        command->phase++;
        /* Fall through once the delay has elapsed. */
    case 0x103:
        if (func_080D8B4C())
            break;
        if (func_080D8858(state->actor, 0)) {
            void *object;

            object = func_080DD4A4(state->actor, 0);
            state->position_source = func_080DD748(object, &state->x,
                                                   &state->y, &state->z);
            if (func_080DD73C(state->position_source))
                state->y += 16;
            state->particles[0] = func_080D5E80(data_084F6130, 4,
                state->x, state->y - 16, state->z, 0x39F, 6);
            state->particles[1] = func_080D5E80(data_084FF2AC, 0,
                state->x, state->y, state->z, 0x359, 6);
            state->particles[2] = func_080D5E80(data_084F6130, 5,
                state->x, state->y - 16, state->z, 0x39F, 6);
            func_08011058(state->particles[0], -1);
            func_08011058(state->particles[1], -1);
            func_08011058(state->particles[2], 1);
            state->timeline = func_080D4704(data_0839AA70[state->kind],
                                            context);
            data_0836D4BC(&state->config, &data_0839AA90,
                           sizeof(state->config));
            state->config.animation = data_0839AAA4[state->kind];
            state->config.mode = data_0839AAB4[state->kind];
            if (state->kind == 7 && func_080DD670(object, 23))
                state->config.mode = 10;
            if (state->kind == 4 && func_080DD5EC(object))
                state->config.palette = 0xFFFF;
            state->actor_effect = func_080DCFE4(object, &state->config,
                                                  12, 24, 12, context, 24);
            state->script = func_080DFD8C(data_0839AAC4, 1, 4, 0,
                                          context);
            if (func_080DD5EC(object))
                state->script = func_080DFD8C(data_0839AACC, 1, 4, 24,
                                              context);
            command->phase++;
        } else {
            command->phase = 2;
        }
        break;
    case 0x104:
        if (func_080D5F24(state->particles, 3) &&
            func_080DE1F0(state->output)) {
            state->timeline = func_080D4774(state->timeline);
            if (state->timeline == 0) {
                state->actor_effect = func_080DBA5C(state->actor_effect);
                if (state->actor_effect == 0)
                    command->phase = 2;
            }
        }
        break;
    }
    return 0;
}
