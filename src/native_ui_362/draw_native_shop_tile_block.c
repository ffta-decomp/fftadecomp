typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct NativeShopTileBlock { u8 x,y; u8 unknown02[4]; u16 tiles[42]; };
struct NativeShopTileSurface { u8 unknown00[20]; u16 *tilemap; };
extern void CopyNativeShopTileRectangle(void *,s32,s32,const u16 *,u32,u32);
__asm__(".global CopyNativeShopTileRectangle\n.thumb_set CopyNativeShopTileRectangle,0x0802B4A9\n");
void DrawNativeShopTileBlock(struct NativeShopTileBlock *,u8,u8)
    __asm__("SceneTaskDependency_0006F33C");
void DrawNativeShopTileBlock(struct NativeShopTileBlock *block,u8 x,u8 y)
{
    s32 signed_x;
    s32 signed_y;
    u8 row;
    block->x = x;
    block->y = y;
    CopyNativeShopTileRectangle((void *)0x030008B0,(s8)block->x,(s8)block->y,block->tiles,14,3);
    row = 0;
    signed_y = (s8)y;
    signed_x = (s8)x;
    for (; row < 3; row++) {
        u16 row_offset = (u32)(signed_y + row) << 5;
        u8 column;
        for (column = 0; column < 14; column++) {
            if ((u32)(signed_x + column) <= 31)
                ((struct NativeShopTileSurface *)0x03000990)->tilemap[row_offset + column + signed_x] = 0xA001;
        }
    }
}
