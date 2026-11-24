typedef unsigned char u8;
typedef unsigned int u32;
struct NativeShopTextStrip {
    u8 unknown00[7];
    u8 half_span;
    u8 unknown08[4];
    void *buffer;
    u8 unknown16[104];
    u8 x;
    u8 y;
};
extern void DrawNativeShopStrip(void *, u32, u32, u32, u32);
__asm__(".global DrawNativeShopStrip\n.thumb_set DrawNativeShopStrip,0x0802B2E9\n");
void RenderNativeShopTextStrip(struct NativeShopTextStrip *strip)
    __asm__("SceneTaskDependency_0006EFF0");
void RenderNativeShopTextStrip(struct NativeShopTextStrip *strip)
{
    DrawNativeShopStrip(strip->buffer, strip->x, strip->y,
                       (u8)(strip->half_span * 2), 2);
}
