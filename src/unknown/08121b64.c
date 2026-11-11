typedef unsigned int u32;
extern void *gSceneTaskPool;
extern void *Allocate_08007138(void *pool, u32 byte_count);
void *AllocateSceneTaskBytes(u32 byte_count)
{
    return Allocate_08007138(gSceneTaskPool, byte_count);
}
asm(".global Allocate_08007138\n.thumb_set Allocate_08007138,0x08007139\n"
    ".global gSceneTaskPool\n.set gSceneTaskPool,0x020159c4\n");
