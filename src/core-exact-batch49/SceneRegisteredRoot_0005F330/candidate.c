#include "interfaces.h"

/* Mission-selection commit callback; the parent exposes the alias StepMissionCommit. */
u32 SceneRegisteredRoot_0005F330(void)
{
    u8 state = gMissionSelection->state_1199;

    if (state == 0)
        goto state_zero;
    if (state == 1)
        goto state_one;
    goto state_default;

state_zero:
    if (Call_0800A5EC() == 0) {
        gMissionSelection->state_1199 = 11;
        return 2;
    }
    Call_08013364();
    gMissionSelection->state_1199 = 1;
    goto state_default;

state_one: {
    u32 readiness_result = Call_08011860();
    if ((readiness_result << 16) == 0)
        goto state_default;

    ConfigureMissionRuntime(gRuntimeInterface, 0, 0, 20, 17, 0);
    ClearMissionTaskState_0802A2C0(0, 0, 0, 0);
    gMissionSelection->continuation = 0;
    gMissionSelection->state_1199 = 255;
    return 8;
}

state_default:
    return 7;
}
