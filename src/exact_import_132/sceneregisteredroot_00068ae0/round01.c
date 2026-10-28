#include "interfaces.h"
void UpdateContent167Flow(u8 slot, u8 *state) __asm__("SceneRegisteredRoot_00068AE0");
void UpdateContent167Flow(u8 slot, u8 *state)
{
    switch (*state) {
    case 0: {
        struct Content167Flow **root = &gContent167Flow;
        *root = AllocateContent167Flow(sizeof(struct Content167Flow));
        gContent167Clear((u8 *)gContent167Flow, sizeof(struct Content167Flow));
        ConfigureContent167Tasks(&gContent167Flow->child_group,
            gContent167Flow->child_callbacks, gContent167Flow->child_states, 1);
        AttachContent167Task(&gContent167Flow->child_group, 0, StepContent167Choice);
        ConfigureContent167Window(gContent167Display, gContent167SecondaryDisplay,
            0, 20, 17, 1);
        gContent167Flow->continuation = 1;
        *state = 1;
        break;
    }
    case 1:
        if (gContent167Supervisor == 0) {
            gContent167Flow->continuation = 2;
            *state = 2;
            SetContent167Transition(gContent167Flow->transition, 0);
        }
        break;
    case 2:
        RunContent167Tasks(&gContent167Flow->child_group, 1);
        TickContent167Transition(gContent167Flow->transition);
        *state = gContent167Flow->continuation;
        break;
    case 254:
        if (gContent167Flow != 0) {
            FreeContent167Flow(gContent167Flow);
            gContent167Flow = 0;
        }
        ActivateContent167(167);
        CommitContent167();
        *state = 255;
        break;
    case 255:
        break;
    }
}
