struct BattleSequenceView;
extern void StepBattleObjectSequence(struct BattleSequenceView *state);
__asm__(".global StepBattleObjectSequence\n.thumb_set StepBattleObjectSequence,0x080a8db9");
/* Existing battle-object continuation forwards its live object unchanged. */
void ContinueBattleObjectSequence(struct BattleSequenceView *state)
{
    StepBattleObjectSequence(state);
}
