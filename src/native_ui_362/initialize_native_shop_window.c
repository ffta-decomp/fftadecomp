typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopBufferContext { u8 unknown00[20]; u32 buffer; };
extern struct NativeShopBufferContext gNativeShopWindowRenderA;
extern struct NativeShopBufferContext gNativeShopWindowRenderB;
__asm__(".global gNativeShopWindowRenderA\n.set gNativeShopWindowRenderA,0x030008B0\n"
        ".global gNativeShopWindowRenderB\n.set gNativeShopWindowRenderB,0x03000990\n");
extern void InitializeNativeWindowFields(void *,u32,u32,u8,u8,u8,u8,u16,u8,u16,u16,u8);
extern void ConfigureNativeWindowTransition(void *,u8);
extern void RestoreNativeWindowRequestFlags(void *,u8);
__asm__(".global InitializeNativeWindowFields\n.thumb_set InitializeNativeWindowFields,0x08017425\n"
        ".global ConfigureNativeWindowTransition\n.thumb_set ConfigureNativeWindowTransition,0x08016C91\n"
        ".global RestoreNativeWindowRequestFlags\n.thumb_set RestoreNativeWindowRequestFlags,0x08017D19\n");
void InitializeNativeShopWindow(void *,u8,u8,u8,u8,u16,u8)
    __asm__("SceneTaskDependency_0002A1FC");
void InitializeNativeShopWindow(void *window,u8 field16,u8 field17,u8 field18,
                                u8 field19,u16 field20,u8 transition_mode)
{
    InitializeNativeWindowFields(window,
        gNativeShopWindowRenderA.buffer,
        gNativeShopWindowRenderB.buffer,
        field16,field17,field18,field19,field20,32,5,1,12);
    ConfigureNativeWindowTransition(window,transition_mode);
    RestoreNativeWindowRequestFlags((u8 *)window + 76,0);
    RestoreNativeWindowRequestFlags((u8 *)window + 96,0);
}
