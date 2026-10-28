typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u8 SceneBaseGraphics[];
extern const u8 SceneFlagGraphics[];
extern u8 SceneVramBase[];
extern u8 SceneVramFlag[];
extern u8 SceneRuntime[];
extern u8 *SceneResourceRoot;
extern void CopySceneWords(const void *,void *,u32);
extern u32 ReadGameFlag(u32);
extern void RefreshSceneTiles(void *,u32,u32);
void InitializeFlaggedSceneGraphics(void) asm("CoreFrontier_0002B8E8");
void InitializeFlaggedSceneGraphics(void)
{
    const u8 *source;
    u32 bytes;
    u8 *root;
    register const u8 *first_source asm("r4") = SceneBaseGraphics;
    register u8 *runtime asm("r0");
    asm("" : "+r"(first_source));
    CopySceneWords(first_source,SceneVramBase,528);
    source = SceneFlagGraphics;
    bytes = 384;
    if ((u8)ReadGameFlag(2)) {
        source += bytes;
        bytes = 640;
    }
    CopySceneWords(source,SceneVramFlag,bytes >> 2);
    runtime = SceneRuntime;
    asm("" : "+r"(runtime));
    if ((*(u16 *)(runtime + 148) & 2) != 0) {
        root = SceneResourceRoot;
        if (root != 0)
            RefreshSceneTiles(root + 0x1ffc,288,1);
    }
}
asm(".set SceneBaseGraphics,0x083be6b4\n.set SceneFlagGraphics,0x083bef08\n.set SceneVramBase,0x06015c00\n.set SceneVramFlag,0x06016440\n.set SceneRuntime,0x0200f390\n.set SceneResourceRoot,0x0200f440\n.thumb_set CopySceneWords,0x08141869\n.thumb_set ReadGameFlag,0x080c9541\n.thumb_set RefreshSceneTiles,0x0802c72d\n");
