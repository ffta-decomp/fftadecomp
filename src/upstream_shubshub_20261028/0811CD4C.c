/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0811CD4C.c
 * Original SHA-256: ce10d733c028246a54a0c0ba87073978e86b57cdfcfa9df1144640b37bad19eb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x0811CD4C..0x0811CDCC (128 bytes), including the literal
 * at 0x0811CDA8 containing the data address 0x03003A60. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 index;
    u16 value;
} Command0811CD4C;

typedef struct {
    u8 index;
    u8 value;
    u16 unknown_02;
    void *object;
    void *effect;
} State0811CD4C;

extern u8 data_03003A60[];
extern u8 func_080DBC58(void *object, u32 value);
extern u8 func_080DBC18(void *object, u32 value);
extern void *func_08147D2C(u16 value, u32 duration, u32 mode, void *data);
extern void *func_081484CC(void *effect);

u32 func_0811CD4C(void *context, Command0811CD4C *command, State0811CD4C *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        state->index = command->index;
        state->value = command->value;
        func_080DBC58(state->object, state->value);
        break;
    case 1:
        break;
    case 0x100:
        state->effect = func_08147D2C((u16)(0x100 + (state->value << 4)),
                                    16, 12, &data_03003A60[state->index * 32]);
        command->state++;
        break;
    case 0x101:
        state->effect = func_081484CC(state->effect);
        if (state->effect == 0) {
            func_080DBC18(state->object, state->index);
            command->state = 2;
        }
        break;
    }
    return 0;
}
