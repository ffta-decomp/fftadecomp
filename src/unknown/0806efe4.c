typedef unsigned char u8;
typedef unsigned int u32;
u32 ReadSelectedNativeShopByte(const u8 *) __asm__("SceneTaskDependency_0006EFE4");
u32 ReadSelectedNativeShopByte(const u8 *descriptor)
{
    const u8 *values=descriptor+1;
    return values[descriptor[0]];
}
