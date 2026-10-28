typedef unsigned char u8;
typedef unsigned short u16;
struct NativeShopWindowShadow {
    u16 control;
    u8 unknown02[56];
    volatile u8 byte58,byte59,byte60,byte61,byte62,byte63,byte64,byte65,byte66;
    u8 unknown67;
    volatile u8 byte68;
    u8 unknown69[5];
    volatile u8 byte74,byte75,byte76,byte77;
};
extern struct NativeShopWindowShadow gNativeShopWindowShadow;
__asm__(".global gNativeShopWindowShadow\n.set gNativeShopWindowShadow,0x03000940\n");
void ResetNativeRecordWindowBounds(u8,u8,u8,u8) __asm__("CoreGlobal36_0002A424");
void ResetNativeRecordWindowBounds(u8 left,u8 top,u8 width,u8 height)
{
    if(left==0 && top==0 && width==0 && height==0) {
        gNativeShopWindowShadow.control &= 0xDFFF;
    } else {
        /* In the pinned target compiler, volatile byte-member stores already
         * retain one read before replacement; explicit reads duplicate it.
         * This is RAM shadow, not an invented MMIO/blanket volatile model. */
        gNativeShopWindowShadow.byte68=31;
        gNativeShopWindowShadow.byte66=63;
        gNativeShopWindowShadow.byte59=(u8)(left<<3);
        gNativeShopWindowShadow.byte63=(u8)(top<<3);
        gNativeShopWindowShadow.byte58=(u8)((left+width)<<3);
        gNativeShopWindowShadow.byte62=(u8)((top+height)<<3);
        gNativeShopWindowShadow.control|=0x2000;
    }
}
