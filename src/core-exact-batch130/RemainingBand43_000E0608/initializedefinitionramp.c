#include "../../../src/task_tree_core.h"

typedef signed short s16;

struct DefinitionRamp {
    u16 value;
    s16 remaining;
    s16 error;
    u16 step;
    u16 period;
    u16 magnitude;
};
typedef char DefinitionRampMustBe12Bytes[sizeof(struct DefinitionRamp)==12?1:-1];
void InitializeDefinitionRamp(struct DefinitionRamp *state, u16 start, u16 target, u16 duration)
{
    int delta;
    state->value = start;
    state->remaining = duration;
    state->error = (s16)duration >> 1;
    state->period = duration;
    delta = (s16)target - (s16)start;
    state->magnitude = delta;
    if ((s16)delta < 0) {
        state->step = 0xffff;
        state->magnitude = -delta;
    } else
        state->step = 1;
}
