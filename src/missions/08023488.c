/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;typedef unsigned int u32;
struct Scene {u8 prefix,request,flags,gap3[3],substate,gap7[85];void *allocation;};
struct PackedMode {u8 value:2;u8 remaining:6;} __attribute__((packed));
struct GameContext {u8 prefix[179],saved_mode,gap180[0xEF2-180];struct PackedMode mode;};
extern struct Scene gScene;
extern struct GameContext gGame;
extern void (*gCopyRoutine)(void*,const void*,u32);
extern u8 gCopyScratch[];
extern void *AllocateModal(u32);
extern void ReleaseModal(void*),BeginTransition(void),BeginModal(void*),RebuildBattleState(void),CallCopyViaR3(void*,const void*,u32,u32);
extern u8 TransitionReady(void),ModalReady(void);
extern const u8 *GetModeRecord(u8);
__asm__(".global gScene\n.set gScene,0x0200F390");
__asm__(".global gGame\n.set gGame,0x020020D0");
__asm__(".global gCopyRoutine\n.set gCopyRoutine,0x0836D4BC");
__asm__(".global gCopyScratch\n.set gCopyScratch,0x030039F8");
__asm__(".global AllocateModal\n.thumb_set AllocateModal,0x08022841");
__asm__(".global ReleaseModal\n.thumb_set ReleaseModal,0x08022855");
__asm__(".global BeginTransition\n.thumb_set BeginTransition,0x080A9549");
__asm__(".global BeginModal\n.thumb_set BeginModal,0x0800975D");
__asm__(".global RebuildBattleState\n.thumb_set RebuildBattleState,0x08023131");
__asm__(".global CallCopyViaR3\n.thumb_set CallCopyViaR3,0x08142251");
__asm__(".global TransitionReady\n.thumb_set TransitionReady,0x080A9589");
__asm__(".global ModalReady\n.thumb_set ModalReady,0x08008881");
__asm__(".global GetModeRecord\n.thumb_set GetModeRecord,0x080CBA85");

u32 AdvanceSavedModeSelection(void)
{
    switch (gScene.substate) {
    case 0:
        gScene.allocation=AllocateModal(0x1BD0);
        BeginTransition();
        gCopyRoutine(gCopyScratch,GetModeRecord(12)+24,2);
        gScene.substate=1;
        break;
    case 1:
        if (TransitionReady()) {
            gGame.saved_mode=gGame.mode.value;
            BeginModal(gScene.allocation);
            gScene.substate=2;
        }
        break;
    case 2:
        if (ModalReady()) {
            ReleaseModal(gScene.allocation);
            gScene.allocation=0;
            gScene.substate=3;
        }
        break;
    case 3:
        if (gGame.saved_mode!=gGame.mode.value) RebuildBattleState();
        gScene.flags=128;
        gScene.request=0;
        return 1;
    }
    return 16;
}
