typedef unsigned int u32;
struct CoordinateTransition;
extern struct CoordinateTransition gBattleCoordinateTransition;
extern u32 AdvanceCoordinateTransition(struct CoordinateTransition *);
u32 PollBattleCoordinateTransition(void)
{
    return AdvanceCoordinateTransition(&gBattleCoordinateTransition);
}
asm(".global gBattleCoordinateTransition\n.set gBattleCoordinateTransition,0x0200F4C0\n.global AdvanceCoordinateTransition\n.thumb_set AdvanceCoordinateTransition,0x08092391\n");
