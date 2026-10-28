typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
u8 * SetNativeShopStripParameter04(u8 *,u32) __asm__("SceneTaskDependency_0006F0D8");
u8 * SetNativeShopStripParameter04(u8 *object,u32 raw_value)
{
    *(u16 *)(object+4) = raw_value;
    return object;
}
