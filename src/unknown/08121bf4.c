typedef unsigned char u8;
typedef unsigned int u32;
struct BattleActionRegistry;
struct BattleSceneWorkBuffer;
struct SceneBattleWorkView { u8 prefix[84]; struct BattleSceneWorkBuffer *battle_work; };
typedef char WorkFieldOffset[(u32)&(((struct SceneBattleWorkView *)0)->battle_work)==84?1:-1];
#define CURRENT_SCENE (*(struct SceneBattleWorkView **)0x020159cc)
extern struct BattleActionRegistry *GetContentConsumerContext(void);
extern struct BattleSceneWorkBuffer *CreateBattleSceneWorkBuffer(void *);
void EnsureSceneBattleWorkBuffer(void)
{
    struct BattleSceneWorkBuffer *work;
    if (CURRENT_SCENE->battle_work == 0) {
        work = CreateBattleSceneWorkBuffer(GetContentConsumerContext());
        CURRENT_SCENE->battle_work = work;
    }
}
asm(".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096d7d\n"
    ".global CreateBattleSceneWorkBuffer\n.thumb_set CreateBattleSceneWorkBuffer,0x0809d90d\n");
