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
void ResetNativeShopWindowShadow(void) __asm__("SceneTaskDependency_0002A534");
void ResetNativeShopWindowShadow(void)
{
    gNativeShopWindowShadow.byte68 = 0;
    gNativeShopWindowShadow.byte66 = 0;
    gNativeShopWindowShadow.byte75 = 0;
    gNativeShopWindowShadow.byte74 = gNativeShopWindowShadow.byte75;
    gNativeShopWindowShadow.byte77 = 0;
    gNativeShopWindowShadow.byte76 = gNativeShopWindowShadow.byte77;
    gNativeShopWindowShadow.byte63 = 0;
    gNativeShopWindowShadow.byte59 = gNativeShopWindowShadow.byte63;
    gNativeShopWindowShadow.byte62 = 0;
    gNativeShopWindowShadow.byte58 = gNativeShopWindowShadow.byte62;
    gNativeShopWindowShadow.byte65 = 0;
    gNativeShopWindowShadow.byte61 = gNativeShopWindowShadow.byte65;
    gNativeShopWindowShadow.byte64 = 0;
    gNativeShopWindowShadow.byte60 = gNativeShopWindowShadow.byte64;
    gNativeShopWindowShadow.control &= 0xDFFF;
    gNativeShopWindowShadow.control &= 0xBFFF;
}
