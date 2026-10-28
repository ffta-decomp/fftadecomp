typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 NativeIconTileScratch[];
extern u8 *NativeIconTextRoot;
extern void LoadNativeIconTile(u8 *,u8) asm("RetailCall_080cb9b0");
extern void CopyNativeIconHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u32 RenderNativeIconText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
void RenderNativeIconTilemapAndText(u8 *,u16 *,u32,const u8 *,u32,u32) asm("CoreRegion_0003776C");
void RenderNativeIconTilemapAndText(u8 *buffer,u16 *tilemap,u32 icon_id,const u8 *text,u32 initial_tile,u32 stride)
{
    u16 tile=initial_tile;
    u8 *scratch=NativeIconTileScratch;
    register u32 row_byte_offset asm("r4");
    register u16 *second_row asm("r4");
    u8 *context;
    tilemap[0]=tile++;
    tilemap[1]=tile++;
    row_byte_offset=stride*2;
    asm("" : "+r"(row_byte_offset));
    second_row=(u16 *)(row_byte_offset+(u32)tilemap);
    asm("" : "+r"(second_row));
    second_row[0]=tile++;
    second_row[1]=tile;
    LoadNativeIconTile(scratch,(u8)icon_id);
    CopyNativeIconHalfwords(scratch,buffer,64);
    context=NativeIconTextRoot+3148;
    buffer += 128;
    RenderNativeIconText(context,(u32)buffer,text,0,1);
}
__asm__(".global NativeIconTileScratch\n.set NativeIconTileScratch,0x02003cb0\n"
        ".global NativeIconTextRoot\n.set NativeIconTextRoot,0x03002810\n"
        ".global RetailCall_080cb9b0\n.thumb_set RetailCall_080cb9b0,0x080cb9b1\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n");
