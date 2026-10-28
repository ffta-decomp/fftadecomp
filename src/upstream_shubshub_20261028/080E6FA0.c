/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E6FA0.c
 * Original SHA-256: ac68beac8343cfd0cfac3f61fb943e5153b28554292dd492ffe503af7cdebe9a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E6FA0..0x080E7130: 400 bytes, 157 instructions. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 variant;
} EffectCommand;

typedef struct {
    u8 unknown_00[2];
    u8 variant;
    u8 unknown_03;
    s16 x;
    s16 y;
    u32 position;
    void *effect;
    void *animation;
    void *overlays[3];
    void *transition;
    void *object;
    void *attachment;
    void *controller;
} EffectState;

extern const u8 data_083976A4[];
extern const u8 data_088EDC04[];
extern const u8 data_0894D7E4[];
extern const u8 data_08949714[];
extern const u8 data_08949728[];
extern const u8 data_0894973C[];
extern const u8 data_083976BC[];
extern const u8 data_083976D0[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *descriptor, u32 mode,
                         u32 priority, u32 flags, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *transition);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void func_080D49FC(u32 index, u32 mode, u32 value, s16 x, s16 y);
extern void *func_080D4B64(u32 index, const void *asset, u32 id, u32 priority);
extern u32 func_080035A8(u32 index);
extern void *func_080D3E9C(const void *descriptor, void *parent);
extern void *func_080D4704(const void *descriptor, void *parent);
extern void *func_080DCFE4(void *object, const void *descriptor, u32 mode,
                         u32 value, u32 priority, void *parent, u32 flags);
extern void *func_080DFD8C(const void *descriptor, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern void *func_080D3F08(void *animation);
extern u8 func_080D48DC(void **overlays, u32 count);
extern void *func_080D4D2C(void *effect, u32 mode);
extern void *func_080DBA5C(void *attachment);

u32 func_080E6FA0(void *task, EffectCommand *command, EffectState *state)
{
    void *object;
    u32 mode;
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->state) {
    case 0:
        state->variant = command->variant;
        state->object = command->object;
        mode = 2;
        if (state->variant) {
            mode = 0;
        }
        state->transition = func_080E03F8(state->object, data_083976A4, mode,
                                         1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->transition = func_080E05DC(state->transition);
        if (state->transition) {
            break;
        }
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        object = func_080DD4A4(state->object, 0);
        state->position = func_080DD748(object, &state->x, &state->y, 0);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->effect = func_080D4B64(0, data_088EDC04, 0x3CB, 6);
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        state->animation = func_080D3E9C(data_0894D7E4, task);
        state->overlays[0] = func_080D4704(data_08949714, task);
        state->overlays[1] = func_080D4704(data_08949728, task);
        state->overlays[2] = func_080D4704(data_0894973C, task);
        state->attachment = func_080DCFE4(object, data_083976BC, 0xC,
                                         0x2E, 0xC, task, 0x2E);
        state->controller = func_080DFD8C(data_083976D0, 1, 4, 0, task);
        command->state++;
        break;
    case 0x101:
        state->animation = func_080D3F08(state->animation);
        if (state->animation) {
            break;
        }
        if (!func_080D48DC(state->overlays, 3)) {
            break;
        }
        state->effect = func_080D4D2C(state->effect, 0);
        if (state->effect) {
            break;
        }
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        state->attachment = func_080DBA5C(state->attachment);
        if (state->attachment) {
            break;
        }
        command->state = 2;
        break;
    }
    return 0;
}
