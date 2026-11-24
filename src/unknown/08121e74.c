typedef unsigned char u8;
extern u8 *gSceneTaskPool;
extern u8 *gSceneTaskPoolBacking;
extern void ClearFirstWord(void *);
extern void FreeGlobalPoolBytes(void *);
void ReleaseSceneTaskPool(void)
{
    ClearFirstWord(gSceneTaskPool);
    FreeGlobalPoolBytes(gSceneTaskPoolBacking);
    gSceneTaskPool = 0;
    gSceneTaskPoolBacking = 0;
}
asm(".global ClearFirstWord\n.thumb_set ClearFirstWord,0x0800718d\n"
    ".global FreeGlobalPoolBytes\n.thumb_set FreeGlobalPoolBytes,0x08022855\n"
    ".global gSceneTaskPool\n.set gSceneTaskPool,0x020159c4\n"
    ".global gSceneTaskPoolBacking\n.set gSceneTaskPoolBacking,0x020159c8\n");
