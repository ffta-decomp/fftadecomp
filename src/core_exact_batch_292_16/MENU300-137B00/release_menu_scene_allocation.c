extern void *gMenuScenePool;
extern void Free_08007170(void *pool, void *allocation);
asm(".global gMenuScenePool\n.set gMenuScenePool,0x0201c3c8\n.global Free_08007170\n.thumb_set Free_08007170,0x08007171");

void CoreGlobal36_00137B00(void *allocation)
{
    Free_08007170(gMenuScenePool, allocation);
}
