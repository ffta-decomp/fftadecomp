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
void AdvanceDefinitionRamp(struct DefinitionRamp *state)
{
    u16 remaining = state->remaining;
    if (state->remaining != 0) {
        u32 initial_error = (u16)state->error;
        u32 error = state->magnitude;
        register u32 remaining_count asm("ip");
        register int error_sign_bits asm("r0");
        error = initial_error - error;
        state->error = error;
        /* Test the stored halfword sign before retaining the native countdown. */
        error_sign_bits = error << 16;
        asm("" : : "r" (error_sign_bits));
        remaining_count = remaining;
        if (error_sign_bits < 0) {
            u32 step = state->step;
            u32 period = state->period;
            u32 current_value = state->value;
            u32 next_value;
            register u32 carried_error asm("r3") = error;
            asm("" : "+r" (carried_error));
            do {
                next_value = current_value + step;
                current_value = next_value;
                error = carried_error + period;
                carried_error = error;
                asm("" : "+r" (carried_error));
            } while ((s16)error < 0);
            state->error = error;
            state->value = next_value;
        }
        asm("" : "+r" (remaining_count));
        state->remaining = remaining_count - 1;
    }
}
