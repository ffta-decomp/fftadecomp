typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeNameTileContext {
    u8 prefix[0x300];
    u8 *tile_buffer;
    u8 unknown_304[14];
    u8 edited_name[18];
};
extern void RenderNativeNameTiles(void *,void *,const u8 *,u32,u32,u32,u32) asm("RetailCall_080161d4");
extern void BiosCopyNameTiles(const volatile void *,void *,u32) asm("RetailCall_0814186c");
extern void *GetNativeNameSurface(struct NativeNameTileContext *) asm("RetailCall_0812b4e0");
extern void QueueNativeNameTileCopy(void *,const void *,void *,u32) asm("RetailCall_08000adc");
asm(".global RetailCall_080161d4\n.thumb_set RetailCall_080161d4,0x080161d5\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n.global RetailCall_0812b4e0\n.thumb_set RetailCall_0812b4e0,0x0812b4e1\n.global RetailCall_08000adc\n.thumb_set RetailCall_08000adc,0x08000add\n");
void RefreshNativeNameEditorNameTiles(struct NativeNameTileContext *) asm("CoreRegion_0012AE8C");
void RefreshNativeNameEditorNameTiles(struct NativeNameTileContext *editor)
{
    u8 index;
    volatile u16 zero;
    void *surface;
    RenderNativeNameTiles((u8 *)editor+8,editor->tile_buffer,editor->edited_name,10,0,0,1);
    for(index=0;index<=8;index++) {
        if(editor->edited_name[index*2]==0x40 && editor->edited_name[index*2+1]==0x73) {
            zero=0;
            BiosCopyNameTiles(&zero,editor->tile_buffer+((u32)index<<7),0x01000040);
        }
    }
    surface=GetNativeNameSurface(editor);
    QueueNativeNameTileCopy(surface,editor->tile_buffer,(void *)0x06016600,288);
}
