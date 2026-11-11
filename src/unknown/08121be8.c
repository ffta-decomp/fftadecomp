typedef unsigned char u8;
typedef unsigned int u32;
struct SceneOwnerWorkView { u8 prefix[84]; void *work; };
typedef char WorkOffset[(u32)&(((struct SceneOwnerWorkView *)0)->work)==84?1:-1];
extern struct SceneOwnerWorkView *gSceneOwner;
void *GetSceneBattleWorkBuffer(void)
{
    return gSceneOwner->work;
}
asm(".global gSceneOwner\n.set gSceneOwner,0x020159cc\n");
