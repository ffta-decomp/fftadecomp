typedef unsigned char u8;
typedef unsigned int u32;
struct BattleSceneWorkBuffer;
struct SceneBattleWorkView { u8 prefix[84]; struct BattleSceneWorkBuffer *battle_work; };
typedef char WorkFieldOffset[(u32)&(((struct SceneBattleWorkView *)0)->battle_work)==84?1:-1];
#define CURRENT_SCENE (*(struct SceneBattleWorkView **)0x020159cc)
extern void ReleaseBattleSceneWorkBuffer(void *);
void ClearSceneBattleWorkBuffer(void)
{
    if (CURRENT_SCENE->battle_work != 0) {
        ReleaseBattleSceneWorkBuffer(CURRENT_SCENE->battle_work);
        CURRENT_SCENE->battle_work = 0;
    }
}
asm(".global ReleaseBattleSceneWorkBuffer\n.thumb_set ReleaseBattleSceneWorkBuffer,0x0809d939\n");
