typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeWindowDescriptor {u8 span,unknown01[3];};
extern const u8 gNativeWindowResourceBank[];
extern u8 gNativeWindowTileBase[];
extern const struct NativeWindowDescriptor *GetNativeWindowDescriptor(u32) asm("RetailCall_08018518");
extern u32 DecodeNativeResourceEntries(const void*,void*,u16,u16) asm("RetailCall_08005318");
extern void CopyNativeHalfwords(const void*,void*,u32) asm("RetailCall_0814186C");
u32 LoadNativeWindowDescriptorTiles(void*,u16,u32) asm("CoreFrontier_00018524");
u32 LoadNativeWindowDescriptorTiles(void *scratch,u16 tile_index,u32 input_type)
{
    u32 type=(u8)input_type;
    const struct NativeWindowDescriptor *descriptor=GetNativeWindowDescriptor(type);
    if(type==30) {
        const u8 *bank=gNativeWindowResourceBank;
        /* B2 and then B1 select the two original three-tile pieces. */
        DecodeNativeResourceEntries(bank,scratch,descriptor->unknown01[1],1);
        {
            u32 destination=(u32)tile_index<<5;
            u32 tile_base=(u32)gNativeWindowTileBase;
            destination+=tile_base;
            CopyNativeHalfwords(scratch,(void*)destination,48);
            DecodeNativeResourceEntries(bank,scratch,descriptor->unknown01[0],1);
            /* Bounded native island: full-word next-tile ordinal to byte
             * offset. No memory effects; ADD/LSL set condition codes. */
            asm("add %0,%1,#3\n\tlsl %0,%0,#5"
                : "=&l"(destination) : "l"((u32)tile_index) : "cc");
            destination+=tile_base;
            CopyNativeHalfwords(scratch,(void*)destination,48);
        }
    } else {
        /* For other types B1 is a tile offset within the decoded scratch data. */
        DecodeNativeResourceEntries(gNativeWindowResourceBank,scratch,descriptor->unknown01[1],1);
        {
            const u8 *source=(u8*)scratch+((u32)descriptor->unknown01[0]<<5);
            u32 destination=(u32)tile_index<<5;
            destination+=(u32)gNativeWindowTileBase;
            CopyNativeHalfwords(source,(void*)destination,(u32)descriptor->span<<4);
        }
    }
    return descriptor->span;
}
__asm__(".global gNativeWindowResourceBank\n.set gNativeWindowResourceBank,0x083d5070\n.global gNativeWindowTileBase\n.set gNativeWindowTileBase,0x06008000");
__asm__(".global RetailCall_08018518\n.thumb_set RetailCall_08018518,0x08018519");
__asm__(".global RetailCall_08005318\n.thumb_set RetailCall_08005318,0x08005319");
__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C,0x0814186d");
