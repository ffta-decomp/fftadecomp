typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattlePhaseControllerContextPrefix;
struct BattleOptionalActor;
struct BattleMovementInputState;
struct BattleFrameInput {
    u8 unknown_00[20];
    u16 held;
    u16 pressed;
};
extern struct BattlePhaseControllerContextPrefix *gBattleFrameContext;
extern struct BattleOptionalActor *gBattleFrameOptionalActor;
extern struct BattleFrameInput gBattleFrameInput;
extern struct BattleMovementInputState gBattleFrameMovement;
extern void ResetBattleFrameCounters(void);
extern u32 AdvanceExistingBattlePhase(struct BattlePhaseControllerContextPrefix *, u32, u32);
extern void UpdateExistingBattleFrameDisplay(void);
extern void UpdateExistingBattleFrameOverlay(void);
extern void UpdateExistingOptionalActor(struct BattleOptionalActor *);
extern void UpdateExistingBattleMovement(struct BattleMovementInputState *);
__asm__(".global gBattleFrameContext\n.set gBattleFrameContext,0x0200f4a8\n"
        ".global gBattleFrameOptionalActor\n.set gBattleFrameOptionalActor,0x0200f4b0\n"
        ".global gBattleFrameInput\n.set gBattleFrameInput,0x0200f390\n"
        ".global gBattleFrameMovement\n.set gBattleFrameMovement,0x0200f3ac\n"
        ".global ResetBattleFrameCounters\n.thumb_set ResetBattleFrameCounters,0x08148831\n"
        ".global AdvanceExistingBattlePhase\n.thumb_set AdvanceExistingBattlePhase,0x08092785\n"
        ".global UpdateExistingBattleFrameDisplay\n.thumb_set UpdateExistingBattleFrameDisplay,0x080bd06d\n"
        ".global UpdateExistingBattleFrameOverlay\n.thumb_set UpdateExistingBattleFrameOverlay,0x080a94d5\n"
        ".global UpdateExistingOptionalActor\n.thumb_set UpdateExistingOptionalActor,0x0809a3f5\n"
        ".global UpdateExistingBattleMovement\n.thumb_set UpdateExistingBattleMovement,0x08024815\n");
