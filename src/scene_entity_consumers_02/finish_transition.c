#include "entity_abi.h"
struct TransitionState {u8 first_byte;u8 phase;u8 reserved[0x92];u16 flags;};
void FinishSceneEntityTransition_081258AC(void)
{
    struct TransitionState *state=(struct TransitionState *)0x0200f390;
    state->phase=1;
    state->flags|=1;
    FilterSceneEntitiesForTransition_08124850(255);
}
