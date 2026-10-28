#include "interfaces.h"

void RunBattleFrameTask(void *unused_context, u8 *state)
{
    struct BattlePhaseControllerContextPrefix *context;
    struct BattleOptionalActor *actor;
    switch (*state) {
    case 0:
        *state = 1;
        break;
    case 1:
        ResetBattleFrameCounters();
        context = gBattleFrameContext;
        if (context != 0)
            AdvanceExistingBattlePhase(context, gBattleFrameInput.pressed,
                                       gBattleFrameInput.held);
        UpdateExistingBattleFrameDisplay();
        UpdateExistingBattleFrameOverlay();
        actor = gBattleFrameOptionalActor;
        if (actor != 0)
            UpdateExistingOptionalActor(actor);
        UpdateExistingBattleMovement(&gBattleFrameMovement);
        break;
    }
}
