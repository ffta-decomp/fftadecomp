typedef unsigned char u8;
typedef unsigned int u32;
extern void *AllocateGlobalPoolBytes(u32);
extern u8 *InitializePool_080070C8(u8 *, u32);
extern u8 *gSceneTaskPool;
extern u8 *gSceneTaskPoolBacking;
void CreateSceneTaskPool(void)
{
    u32 byte_count = 20480;
    u8 *backing;
    u8 *pool;
    backing = AllocateGlobalPoolBytes(byte_count);
    pool = InitializePool_080070C8(backing, byte_count);
    gSceneTaskPool = pool;
    gSceneTaskPoolBacking = backing;
}
asm(".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n"
    ".global InitializePool_080070C8\n.thumb_set InitializePool_080070C8,0x080070c9\n"
    ".global gSceneTaskPool\n.set gSceneTaskPool,0x020159c4\n"
    ".global gSceneTaskPoolBacking\n.set gSceneTaskPoolBacking,0x020159c8\n");
