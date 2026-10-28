#include "action_feasibility.h"

u32 TestActionSimulationFeasible(void *actor, void *target, u32 action)
{
    u16 equipment[2];
    struct ActionSimulation *simulation;
    s32 slot;

    action = (u16)action;
    simulation = &ActionSimulation;
    CollectActionEquipment(actor, equipment);
    if (action == 0) {
feasible:
        return 1;
    }

    InitializeActionSimulation(action, equipment[0], 0);
    simulation->actor = actor;
    simulation->target = target;
    simulation->flags |= 2;
    for (slot = 0; slot <= 2; ++slot) {
        SelectActionSlot((u8)slot);
        SetActionTarget(0);
        if ((u8)TestActionSlot() == 0)
            continue;
        MarkActionSlot(slot);
        SetActionTarget(target);
        switch ((u8)ReadActionKind()) {
        case 1:
        case 5:
            return EvaluateActionValue() > 0;
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
            return 0;
        case 8:
            goto feasible;
        }
    }
    return 0;
}
