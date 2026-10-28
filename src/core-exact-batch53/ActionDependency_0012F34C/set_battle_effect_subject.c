typedef unsigned int u32;

typedef struct BattleEffectContextPrefix {
    u32 actor;
    u32 target;
    volatile u32 subject;
} BattleEffectContextPrefix;

typedef char BattleEffectContextPrefixSize[
    sizeof(BattleEffectContextPrefix) == 12 ? 1 : -1];

void SetBattleEffectSubject(u32 subject_pointer)
{
    volatile BattleEffectContextPrefix *context =
        (volatile BattleEffectContextPrefix *)0x0200f3f0;
    context->subject = subject_pointer;
}
