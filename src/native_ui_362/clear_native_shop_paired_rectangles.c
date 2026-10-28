typedef unsigned char u8;
typedef unsigned int u32;
extern void ClearNativeShopRectangle(void *, u32, u32, u32, u32);
__asm__(".global ClearNativeShopRectangle\n.thumb_set ClearNativeShopRectangle,0x0802b2e9");
void ClearNativeShopPairedRectangles(void *, void *, u8, u8)
    __asm__("SceneTaskDependency_0002B2A8");
void ClearNativeShopPairedRectangles(void *first, void *second, u8 x, u8 y)
{
    ClearNativeShopRectangle(first, x, y, 13, 2);
    ClearNativeShopRectangle(second, x, y, 13, 2);
}
