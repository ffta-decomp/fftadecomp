typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct NativeIconLayer {u8 unknown00[16];u8 *buffer;u16 *tiles;} NativeIconLayer;
extern NativeIconLayer NativeSceneIconLayer;
extern u32 ReadNativeSceneIconSelector(void *) asm("RetailCall_08128fc4");
extern void ClearNativeSceneCaption(void *,u16) asm("RetailCall_08013a88");
extern void *AllocateNativeSceneIcon(u32) asm("RetailCall_08121b64");
extern void ReleaseNativeSceneIcon(void *) asm("RetailCall_08121b78");
extern void LoadNativeItemIcon(u8 *,u16) asm("RetailCall_080cb980");
extern u32 ReadNativeItemPaletteNibble(u16) asm("RetailCall_080cb99c");
extern u32 GetNativeTileCoordinate(u32,u32,u32) asm("RetailCall_080161a0");
extern void CopyNativeIconHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u32 ProcessNativeSceneCaption(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern u16 CenterNativeSceneCaption(void *,const void *,const u8 *,u32,u32) asm("RetailCall_0801539c");
extern void ApplyNativeSceneDefinition(int,int) asm("RetailCall_08141570");
u32 StepNativeSceneIconCaption(u8 *) asm("CoreRegion_0012949C");
u32 StepNativeSceneIconCaption(u8 *context)
{
    register u8 *scene asm("r8")=context;
    u8 delay;
    register u8 *delay_slot asm("r1");
    u32 selector;
    u8 *buffer;
    asm("" : "+r"(scene));
    delay_slot=scene+934;
    asm("" : "+r"(delay_slot));
    delay=*delay_slot;
    if (delay!=0) {
        *delay_slot=delay-1;
        return 0;
    }
    selector=(u16)ReadNativeSceneIconSelector(scene);
    buffer=NativeSceneIconLayer.buffer+13824;
    ClearNativeSceneCaption(buffer,28);
    if (selector!=0) {
        u8 *icon=AllocateNativeSceneIcon(128);
        u32 category=selector&0xF000;
        u32 item_index;
        register u32 palette asm("r4");
        u32 palette_bits;
        register u16 *bottom_row asm("r4");
        u32 coordinate;
        u16 *tiles;
        if (category==0x1000)
            item_index=selector&0x0FFF;
        else if (category==0x2000)
            item_index=392;
        else
            item_index=selector&0x0FFF;
        LoadNativeItemIcon(icon,item_index);
        {
            register u32 raw_palette asm("r0")=ReadNativeItemPaletteNibble(item_index);
            raw_palette += 13;
            raw_palette <<= 24;
            asm("" : "+r"(raw_palette));
            palette=raw_palette>>24;
            asm("" : "+r"(palette));
        }
        coordinate=GetNativeTileCoordinate(10,9,32);
        tiles=NativeSceneIconLayer.tiles+(u16)coordinate;
        palette_bits=palette<<12;
        tiles[0]=palette_bits|0x1B0;
        tiles[1]=palette_bits|0x1B1;
        bottom_row=tiles+32;
        asm("" : "+r"(bottom_row));
        *bottom_row=palette_bits|0x1B2;
        tiles[33]=palette_bits|0x1B3;
        CopyNativeIconHalfwords(icon,buffer,64);
        buffer += 128;
        ReleaseNativeSceneIcon(icon);
        ProcessNativeSceneCaption(scene+40,(u32)buffer,scene+936,0,1);
    } else {
        CenterNativeSceneCaption(scene+40,buffer,scene+936,0,14);
    }
    ApplyNativeSceneDefinition(1,123);
    return 1;
}
__asm__(".global NativeSceneIconLayer\n.set NativeSceneIconLayer,0x030008b0\n"
        ".global RetailCall_08128fc4\n.thumb_set RetailCall_08128fc4,0x08128fc5\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n"
        ".global RetailCall_08121b64\n.thumb_set RetailCall_08121b64,0x08121b65\n"
        ".global RetailCall_08121b78\n.thumb_set RetailCall_08121b78,0x08121b79\n"
        ".global RetailCall_080cb980\n.thumb_set RetailCall_080cb980,0x080cb981\n"
        ".global RetailCall_080cb99c\n.thumb_set RetailCall_080cb99c,0x080cb99d\n"
        ".global RetailCall_080161a0\n.thumb_set RetailCall_080161a0,0x080161a1\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0801539c\n.thumb_set RetailCall_0801539c,0x0801539d\n"
        ".global RetailCall_08141570\n.thumb_set RetailCall_08141570,0x08141571\n");
