struct EffectSequence;
struct UnitEffectView;
extern struct EffectSequence gPendingBattleEffectSequence;
extern void InitializeBattleEffectSequence(struct EffectSequence *sequence,
    const struct UnitEffectView *unit);
__asm__(".global gPendingBattleEffectSequence\n.set gPendingBattleEffectSequence, 0x0200f770\n.global InitializeBattleEffectSequence\n.thumb_set InitializeBattleEffectSequence, 0x0809ea61");
/* Preserve the singleton address across initialization, then hand it to polling. */
struct EffectSequence *BeginPendingBattleEffectSequence(const struct UnitEffectView *unit)
{
    struct EffectSequence *sequence = &gPendingBattleEffectSequence;
    InitializeBattleEffectSequence(sequence, unit);
    return sequence;
}
