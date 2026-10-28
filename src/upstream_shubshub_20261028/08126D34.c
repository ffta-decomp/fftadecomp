/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08126D34.c
 * Original SHA-256: 429e2fc67213dd01586dfb7c47c67f1c86cfb7e1bdbc16b96bac63c4c978c999
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct
{
    u8 unknown_00[6];
    u8 completed;
} Subject;

typedef struct
{
    u16 state;
    u16 unknown_02;
    Subject *subject;
    u8 unknown_08[12];
    u16 unit_id;
    s16 action;
    u16 enabled;
} Command;

typedef struct
{
    u8 unknown_00[31];
    s8 layer;
} Animation;

typedef struct
{
    Subject *subject;
    Animation *animation;
    u8 enabled;
} CommandState;

extern void *func_08125578(u8 selector);
extern void *func_08096D7C(void);
extern Animation *func_08099560(void *scene, void *unit);
extern void func_0809A09C(Animation *animation);
extern void func_0809836C(Animation *animation, u16 action, s8 layer, u8 mode);
extern void func_0809A2AC(Animation *animation, u16 action, s8 layer, u8 mode);
extern void func_0809A570(Animation *animation, u32 clear, u32 set);
extern u32 func_08099C64(const Animation *animation);

/* Complete target: 0x08126D34..0x08126DFA, 198 bytes. */
s32 func_08126D34(void *context, Command *command, CommandState *state)
{
    switch (command->state)
    {
    case 0:
    {
        void *unit = func_08125578(command->unit_id);

        state->subject = command->subject;
        state->animation = func_08099560(func_08096D7C(), unit);
        state->enabled = command->enabled;
        func_0809A09C(state->animation);
        if (command->action == 9 && (u16)(command->unit_id - 20) <= 3)
            func_0809836C(state->animation, 13, state->animation->layer, 0);
        else
            func_0809A2AC(state->animation, (u16)command->action * 4,
                          state->animation->layer, 0);

        if (state->enabled)
            func_0809A570(state->animation, 0x100, 2);
        else
            func_0809A570(state->animation, 2, 0);
        break;
    }
    case 1:
        break;
    case 0x100:
        if (func_08099C64(state->animation) || state->enabled)
            command->state = 0x101;
        break;
    case 0x101:
        state->subject->completed = 1;
        command->state = 3;
        break;
    }
    return 0;
}
