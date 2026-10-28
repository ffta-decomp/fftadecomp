#include "interfaces.h"
s32 AdvanceUntilTargetUnit(const void *roster,struct TurnUnitRecord *target,u16 warmup)
    __asm__("RunBattleUntilUnitTurn");
s32 AdvanceUntilTargetUnit(const void *roster,struct TurnUnitRecord *target,u16 warmup)
{
    struct TurnContext *turn;
    s32 count;
    s32 slot;
    struct TurnUnit *selected;
    if (target == 0)
        return -1;
    if (!CanTargetUnitTakeTurn(target->unit)
        || TargetUnitStateEBBit2(target->unit) || TargetUnitStateEABit7(target->unit))
        return -1;
    turn = AllocateTurnContext(0xe1c);
    InitializeTargetTurnContext(turn,roster);
    for (count = 0; count < (s16)warmup; count++) {
        slot = RunTargetTurnManager(turn);
        selected = (struct TurnUnit *)((u32)slot * 264 + (u32)turn + 4);
        selected->charge_time = 0;
        selected->charge_carry = 0;
    }
    for (;;count++) {
        slot = RunTargetTurnManager(turn);
        selected = (struct TurnUnit *)((u32)slot * 264 + (u32)turn + 4);
        selected->charge_time = 0;
        selected->charge_carry = 0;
        if (target == turn->records[slot])
            break;
    }
    FreeTurnContext(turn);
    return count;
}
