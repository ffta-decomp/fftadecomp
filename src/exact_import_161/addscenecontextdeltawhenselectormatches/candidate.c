#include "contract.h"

u32 AddSceneContextDeltaWhenSelectorMatches(ScriptContext *context, const u8 *command)
{
    u32 accepted = 0;
    u8 resolved_slot = ResolveSceneSelector(gSaveSelector.current_selector);
    u8 requested_slot = command[1];
    if (requested_slot == 0) {
        u8 candidate = 1;
        while (resolved_slot != candidate) {
            ++candidate;
            if (candidate > 6)
                goto predicate_done;
        }
        goto apply_delta;
    } else {
        if (resolved_slot == requested_slot)
            accepted = 1;
    }
predicate_done:
    if (accepted == 0)
        goto finished;
apply_delta:
    {
        u32 delta = command[2] | ((u32)command[3] << 8);
        context->pc = context->pc + delta;
    }
finished:
    return 272;
}
