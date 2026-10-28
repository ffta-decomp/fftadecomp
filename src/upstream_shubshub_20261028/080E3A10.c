/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E3A10.c
 * Original SHA-256: 7936173990536e2b1671755fea72bf9dff87b1f1fd06a6a1b07336e25b0b0fbd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[6];
    void *object;
} EffectTask;

typedef struct {
    void *object;
    void *startup;
    void *effect;
} EffectState;

extern const u8 data_08396498[];
extern u8 data_0600F9E0[];
extern u8 data_06005800[];
extern void func_080D38B4(void);
extern void *func_080D7A70(const void *data, u32 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void *func_080DFA70(void *object, u32 mode, u32 first, u32 second,
                          u32 first_resource, u32 second_resource,
                          void *first_destination, void *second_destination,
                          u32 first_option, u32 second_option, void *parent);
extern void *func_080DBA5C(void *effect);

u32 func_080E3A10(void *object, EffectTask *task, EffectState *state)
{
    switch (task->state) {
    case 0:
        state->object = task->object;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->startup = func_080D7A70(data_08396498, 3, object);
        task->state++;
        break;
    case 0x101:
        state->startup = func_080D7ABC(state->startup);
        if (state->startup == 0) {
            state->effect = func_080DFA70(state->object, 2, 6, 6,
                                         0x3ED, 0x3E6,
                                         data_0600F9E0, data_06005800,
                                         0, 0, object);
            task->state++;
        }
        break;
    case 0x102:
        state->effect = func_080DBA5C(state->effect);
        if (state->effect == 0)
            task->state = 2;
        break;
    }
    return 0;
}
