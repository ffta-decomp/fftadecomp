#include "interfaces.h"
/* This delta precedes the dispatcher's ordinary descriptor-length advance. */
u32 BranchOnFirstStoryChoice(struct ChoiceScriptState *script,
                             const struct ChoiceBranchCommand *command)
{
    if((u8)ReadConfirmedStoryChoice()==0) {
        int delta=command->delta_low;
        delta|=command->delta_high<<8;
        script->offset+=delta;
    }
    return 0x110;
}
