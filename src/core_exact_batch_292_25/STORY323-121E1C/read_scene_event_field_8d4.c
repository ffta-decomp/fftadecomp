typedef unsigned char u8;
struct SceneEventRoot { u8 unknown00[0x8d4]; void *field8d4; };
extern struct SceneEventRoot *gSceneEventRoot;
void *ReadSceneEventField8D4(void) __asm__("SceneActionDependency_00121E1C");
void *ReadSceneEventField8D4(void)
{
    return gSceneEventRoot->field8d4;
}
__asm__(".global gSceneEventRoot\n.set gSceneEventRoot,0x020159cc");
