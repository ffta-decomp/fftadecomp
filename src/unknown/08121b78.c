extern void *gSceneTaskPool;
extern void FreePoolAllocation(void *pool, void *payload);
void ReleaseSceneTaskAllocation(void *payload)
{
    FreePoolAllocation(gSceneTaskPool, payload);
}
asm(".global FreePoolAllocation\n.thumb_set FreePoolAllocation,0x08007171\n"
    ".global gSceneTaskPool\n.set gSceneTaskPool,0x020159c4\n");
