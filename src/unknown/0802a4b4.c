typedef unsigned char u8;
typedef unsigned short u16;
struct NativeShopWindowShadow {
    u16 control;
    u8 unknown02[56];
    volatile u8 byte58,byte59,byte60,byte61,byte62,byte63,byte64,byte65,byte66;
    u8 unknown67;
    volatile u8 byte68;
    u8 unknown69[5];
    volatile u8 byte74,byte75,byte76,byte77;
};
extern struct NativeShopWindowShadow gNativeShopWindowShadow;
__asm__(".global gNativeShopWindowShadow\n.set gNativeShopWindowShadow,0x03000940\n");
void ConfigureNativeShopPixelWindow(u8,u8,u8,u8) __asm__("SceneTaskDependency_0002A4B4");
void ConfigureNativeShopPixelWindow(u8 left,u8 top,u8 right,u8 bottom)
{
    gNativeShopWindowShadow.byte68 = 31;
    gNativeShopWindowShadow.byte66 = 63;
    gNativeShopWindowShadow.byte74 = 72;
    gNativeShopWindowShadow.byte75 = 51;
    gNativeShopWindowShadow.byte76 = 14;
    gNativeShopWindowShadow.byte77 = 9;
    gNativeShopWindowShadow.byte59 = left;
    gNativeShopWindowShadow.byte63 = top;
    gNativeShopWindowShadow.byte58 = right;
    gNativeShopWindowShadow.byte62 = bottom;
    gNativeShopWindowShadow.control |= 0x2000;
}
