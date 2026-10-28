/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E2E24.c
 * Original SHA-256: 549ecaa6af427cec15aea62ebf9b627a0e4524b9bba9e126f2f3909ad9373ad9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E2E24..0x080E2FA4: 384 bytes, 153 instructions. */
typedef struct {
    u16 state;
    u8 unknown_02[6];
    u32 argument;
} EffectCommand;

typedef struct {
    s16 value;
    u8 unknown_02[0xA];
} Motion;

typedef struct {
    s16 x;
    s16 y;
    u32 entity;
    Motion motion;
    void *delay;
    void *effect;
    void *animation;
    void *overlay;
    void *attachment;
    void *controller;
} EffectState;

extern const u8 data_08395EC0[];
extern const u8 data_088EF35C[];
extern const u8 data_0894D900[];
extern const u8 data_08949D30[];
extern const u8 data_08395ED8[];
extern u16 g_control_flags_03000940;

extern void func_080D38B4(void);
extern void *func_080D7A70(const void *descriptor, u32 mode, void *parent);
extern void *func_080D7ABC(void *delay);
extern void func_080DBDC8(u32 entity, s16 *x, s16 *y);
extern void func_080D49FC(u32 index, u32 mode, u32 value, s16 x, s16 y);
extern void *func_080D4B64(u32 index, const void *asset, u32 id, u32 priority);
extern u32 func_080035A8(u32 index);
extern void func_080E0608(Motion *motion, s16 start, s16 end, u32 duration);
extern void func_080E064C(Motion *motion);
extern void *func_080D3E9C(const void *descriptor, void *parent);
extern void *func_080D4704(const void *descriptor, void *parent);
extern void *func_080DFD8C(const void *descriptor, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern void *func_080DBB14(u32 entity, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern void *func_080D4D2C(void *effect, u32 mode);
extern void *func_080D3F08(void *animation);
extern void *func_080D4774(void *overlay);
extern void *func_080DBA5C(void *attachment);

u32 func_080E2E24(void *task, EffectCommand *command, EffectState *state)
{
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->state) {
    case 0:
        state->entity = command->argument;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->delay = func_080D7A70(data_08395EC0, 2, task);
        command->state++;
        break;
    case 0x101:
        state->delay = func_080D7ABC(state->delay);
        if (state->delay) {
            break;
        }
        func_080DBDC8(state->entity, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, (s16)(state->y - 0x10));
        state->effect = func_080D4B64(0, data_088EF35C, 0x3E6, 6);
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        func_080E0608(&state->motion, (s16)(state->y - 0x10),
                      (s16)(state->y - 0x18), 0x20);
        state->animation = func_080D3E9C(data_0894D900, task);
        state->overlay = func_080D4704(data_08949D30, task);
        state->controller = func_080DFD8C(data_08395ED8, 1, 4, 0, task);
        state->attachment = func_080DBB14(state->entity, 1, 0xC, 0, task);
        command->state++;
        break;
    case 0x102:
        if (state->effect) {
            func_080E064C(&state->motion);
            func_0800BC08(0, state->x, state->motion.value);
        }
        state->effect = func_080D4D2C(state->effect, 0);
        if (state->effect) {
            break;
        }
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        state->animation = func_080D3F08(state->animation);
        if (state->animation) {
            break;
        }
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay) {
            break;
        }
        state->attachment = func_080DBA5C(state->attachment);
        if (state->attachment) {
            break;
        }
        command->state = 2;
        break;
    }
    return 0;
}
