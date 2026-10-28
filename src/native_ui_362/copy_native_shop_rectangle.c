typedef unsigned char u8;
typedef signed char s8;
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
void CopyNativeShopRectangle(struct NativeShopTilemapView *,u8,u8,const u16 *,u8,u8)
    __asm__("CoreDependency29_0002B4A8");
void CopyNativeShopRectangle(struct NativeShopTilemapView *surface,
                             u8 x,u8 y,const u16 *source,u8 width,u8 height)
{
    u16 *tilemap=surface->tilemap;
    u8 row;
    for (row=0;row<height;row++) {
        u16 row_offset=surface->row_stride*(row+(s8)y);
        u32 source_row=width*row;
        u8 column;
        for (column=0;column<width;column++)
            if ((u32)((s8)x+column)<=30)
                tilemap[row_offset+column+(s8)x]=source[source_row+column];
    }
}
