#include "interfaces.h"

void UpdateContent167PairedFlow(u8 slot, u8 *state) __asm__("SceneRegisteredRoot_0005873C");
void UpdateContent167PairedFlow(u8 slot, u8 *state)
{
    switch (*state) {
    case 0: {
        struct Content167PairedFlow **root = &gContent167PairedFlow;
        *root = AllocateContent167Flow(sizeof(struct Content167PairedFlow));
        gContent167Clear((u8 *)gContent167PairedFlow, sizeof(struct Content167PairedFlow));
        ConfigureContent167Tasks(&gContent167PairedFlow->child_group,
            gContent167PairedFlow->child_callbacks, gContent167PairedFlow->child_states, 2);
        AttachContent167Task(&gContent167PairedFlow->child_group, 1, StepContent167ChildOne);
        gContent167PairedFlow->continuation = 1;
        *state = 1;
        break;
    }
    case 1:
        if (gContent167Supervisor == 0) {
            gContent167PairedFlow->continuation = 2;
            *state = 2;
            AttachContent167Task(&gContent167PairedFlow->child_group, 0, StepContent167ChildZero);
            SetContent167Transition(gContent167PairedFlow->transition, 0);
        }
        break;
    case 2:
        TickContent167Transition(gContent167PairedFlow->transition);
        *state = gContent167PairedFlow->continuation;
        break;
    case 253:
        /* The content handoff retains both child slots until explicit teardown. */
        break;
    case 254:
        ActivateContent167(167);
        CommitContent167();
        *state = 253;
        break;
    case 255:
        if (gContent167PairedFlow != 0) {
            /* Child one closes before the retained context is destroyed. */
            gContent167PairedFlow->child_states[1] = 255;
            RunContent167Tasks(&gContent167PairedFlow->child_group, 2);
            FreeContent167Flow(gContent167PairedFlow);
            gContent167PairedFlow = 0;
        }
        break;
    }
    if (gContent167PairedFlow != 0)
        RunContent167Tasks(&gContent167PairedFlow->child_group, 2);
}
