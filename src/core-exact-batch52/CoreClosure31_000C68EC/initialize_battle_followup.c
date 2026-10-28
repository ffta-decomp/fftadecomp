#include "interfaces.h"

/* The continuation consumes the queued phase IDs; their individual roles remain tentative. */
void InitializeBattleFollowup(struct BattleFollowupState *state,
                             struct FollowupContext *context)
{
    struct FollowupRecord *records[13];
    s32 record_count;
    s32 index;
    u16 previous_depth;
    ClearFollowupMemory(state, sizeof(*state));
    state->context = context;
    record_count = CollectFollowupRecords(context, records);
    for (index = 0; index < record_count; index++) {
        if ((u8)IsFollowupUnitInRoster(records[index]->unit) != 0) {
            state->selected_units[state->selected_count] = records[index]->unit;
            state->selected_count++;
            if (state->selected_count > 1) break;
        }
    }
    state->phase = 18;
    previous_depth = state->phase_depth++;
    state->phase_stack[previous_depth] = state->phase;
    state->phase = 5;
    previous_depth = state->phase_depth++;
    state->phase_stack[previous_depth] = state->phase;
    state->phase = 8;
    previous_depth = state->phase_depth++;
    state->phase_stack[previous_depth] = state->phase;
    state->phase = 2;
    previous_depth = state->phase_depth++;
    state->phase_stack[previous_depth] = state->phase;
    state->phase = 0;
}
