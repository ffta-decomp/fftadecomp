typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopTilemapView {
    u8 unknown00[12];
    u8 row_stride;
    u8 unknown0d[7];
    u16 *tilemap;
};
typedef char NativeShopStrideOffset[(u32)&((struct NativeShopTilemapView *)0)->row_stride==12?1:-1];
typedef char NativeShopTilemapOffset[(u32)&((struct NativeShopTilemapView *)0)->tilemap==20?1:-1];
void ClearNativeShopRectangle(struct NativeShopTilemapView *,u8,u8,u8,u8)
    __asm__("SceneTaskDependency_0002B2E8");
void ClearNativeShopRectangle(struct NativeShopTilemapView *surface,
                              u8 x,u8 y,u8 width,u8 height)
{
    u16 row;
    for (row=0;row<height;row++) {
        u16 row_offset=surface->row_stride*(row+y);
        u16 column;
        for (column=0;column<width;column++)
            surface->tilemap[row_offset+x+column]=0;
    }
}
