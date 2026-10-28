typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
void SetNativeShopStripParameter02(u8 *,u32) __asm__("SceneTaskDependency_0006F0D4");
void SetNativeShopStripParameter02(u8 *object,u32 raw_value)
{
    object[2] = raw_value;
}
