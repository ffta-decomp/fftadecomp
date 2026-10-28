typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopValuePanel {
    u8 *buffer;
    u8 unknown04[12];
    u8 origin;
    u8 row;
    u8 unknown18[4];
    u8 stride;
};
extern void FillNativeShopTiles(u16 *, u16, u8, u16);
__asm__(".global FillNativeShopTiles\n.thumb_set FillNativeShopTiles,0x0802ACA1\n");
void UpdateNativeShopValuePair(struct NativeShopValuePanel *, u16, u16)
    __asm__("SceneTaskDependency_00070120");
void UpdateNativeShopValuePair(struct NativeShopValuePanel *panel, u16 first, u16 second)
{
    {
        register u32 offset __asm__("r2") = panel->stride;
        offset *= panel->row + 1;
        /* The initialized first product is consumed in its native R2 carrier. */
        __asm__("" : "+r" (offset));
        offset += panel->origin;
        offset <<= 1;
        offset += 26;
        FillNativeShopTiles((u16 *)(panel->buffer + offset), first, 12, 3);
    }
    {
        register u32 offset __asm__("r1") = panel->stride;
        offset *= panel->row + 1;
        /* The independent post-call product is consumed in native R1. */
        __asm__("" : "+r" (offset));
        offset += panel->origin;
        offset <<= 1;
        offset += 34;
        FillNativeShopTiles((u16 *)(panel->buffer + offset), second, 12, 3);
    }
}
