extern void *gMenuScenePool;
extern void *Allocate_08007138(void *pool, unsigned int requested_bytes);
asm(".global gMenuScenePool\n.set gMenuScenePool,0x0201c3c8\n.global Allocate_08007138\n.thumb_set Allocate_08007138,0x08007139");

void *CoreGlobal36_00137AEC(unsigned int requested_bytes)
{
    return Allocate_08007138(gMenuScenePool, requested_bytes);
}
