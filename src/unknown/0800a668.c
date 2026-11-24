extern void *gCurrentResourceContext;
extern void ReleaseResourceInContext(void *context, void *resource);
__asm__(".global gCurrentResourceContext\n.set gCurrentResourceContext,0x02008ff4\n.global ReleaseResourceInContext\n.thumb_set ReleaseResourceInContext,0x08007171");
void ReleaseCurrentSceneResource(void *resource)
{
    ReleaseResourceInContext(gCurrentResourceContext, resource);
}
