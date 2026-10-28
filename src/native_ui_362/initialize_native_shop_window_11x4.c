typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeWindowLayerPrefix {u8 opaque00[20];u32 buffer;};
struct NativeShopWindowPrefix {
    u8 opaque00[18]; u8 columns,rows;
    u8 opaque14[36]; void *tile_buffer;
    u8 opaque3c[10]; u16 field46;
    u8 opaque48[3]; u8 marker4b;
};
extern struct NativeWindowLayerPrefix gNativeWindowLayerA,gNativeWindowLayerB;
extern void ConfigureNativeManagedWindow(struct NativeShopWindowPrefix*,u32,u32,u8,u8,u8,u8,u16,u8,u16,u16,u8);
extern void SetNativeManagedWindowData(struct NativeShopWindowPrefix*,void*,u16,u16);
extern void BiosCpuSet(const void*,void*,u32);
extern void AdvanceNativeManagedWindow(struct NativeShopWindowPrefix*,u32);
__asm__(".global gNativeWindowLayerA\n.set gNativeWindowLayerA,0x030008b0\n"
        ".global gNativeWindowLayerB\n.set gNativeWindowLayerB,0x03000990\n"
        ".global ConfigureNativeManagedWindow\n.thumb_set ConfigureNativeManagedWindow,0x08017425\n"
        ".global SetNativeManagedWindowData\n.thumb_set SetNativeManagedWindowData,0x08016211\n"
        ".global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n"
        ".global AdvanceNativeManagedWindow\n.thumb_set AdvanceNativeManagedWindow,0x08016c91");
void InitializeNativeShopWindow11x4(struct NativeShopWindowPrefix*,void*,u16,u8,u8) __asm__("CoreClosure31_00053BE0");
void InitializeNativeShopWindow11x4(struct NativeShopWindowPrefix *window,void *content,
                                   u16 first_value,u8 x,u8 y)
{
    u16 zero;
    ConfigureNativeManagedWindow(window,gNativeWindowLayerA.buffer,gNativeWindowLayerB.buffer,
                                  x,y,11,4,2048,32,13,3,11);
    SetNativeManagedWindowData(window,content,first_value,2);
    window->marker4b=11;
    window->field46=0;
    zero=0;
    BiosCpuSet(&zero,window->tile_buffer,0x01000000u | ((u32)window->columns*window->rows));
    AdvanceNativeManagedWindow(window,1);
}
