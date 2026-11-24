typedef unsigned int u32;

extern void SetSceneCallbacks(u32 first, u32 second);
__asm__(".global SetSceneCallbacks\n.thumb_set SetSceneCallbacks,0x08013405");

void CoreRegion30_000615B0(void)
{
    SetSceneCallbacks(0x08061189u, 0x0806119Du);
}
