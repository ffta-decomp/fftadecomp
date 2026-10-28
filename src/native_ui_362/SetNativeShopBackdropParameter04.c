typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
void SetNativeShopBackdropParameter04(u8 *,u32) __asm__("SceneTaskDependency_0006F3C4");
void SetNativeShopBackdropParameter04(u8 *object,u32 raw_value)
{
    *(u16 *)(object+4) = raw_value;
}
