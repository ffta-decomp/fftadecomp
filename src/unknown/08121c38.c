typedef unsigned char u8;
struct BattleWorkset;
struct SceneBattleWorkView { u8 reserved[84]; struct BattleWorkset *workset; };
extern struct SceneBattleWorkView *gSceneBattleWork;
extern unsigned int StepBattleWorkset(struct BattleWorkset *);
unsigned int PollSceneBattleWorkset(void)
{
    struct BattleWorkset *workset = gSceneBattleWork->workset;
    unsigned int result;
    if (workset == 0)
        result = 1;
    else
        result = (u8)StepBattleWorkset(workset);
    return result;
}
asm(".global gSceneBattleWork\n.set gSceneBattleWork,0x020159cc\n"
    ".global StepBattleWorkset\n.thumb_set StepBattleWorkset,0x0809d2f9\n");
