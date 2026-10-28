typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct NativeCurrencySurface { u8 unknown00[20]; u16 *tilemap; };
struct CurrencyRam { u8 unknown00[0x1F64]; u32 currency; };
extern struct CurrencyRam gNativeShopCurrencyRam;
extern void FormatNativeCurrencyTiles(u16 *,u16,u32,u16);
extern void QueueNativeDisplayDefinition(int,int);
extern void CopyNativeCurrencyTiles(const void *,void *,u32);
__asm__(".global gNativeShopCurrencyRam\n.set gNativeShopCurrencyRam,0x02000000\n"
        ".global FormatNativeCurrencyTiles\n.thumb_set FormatNativeCurrencyTiles,0x08029DD5\n"
        ".global QueueNativeDisplayDefinition\n.thumb_set QueueNativeDisplayDefinition,0x08141571\n"
        ".global CopyNativeCurrencyTiles\n.thumb_set CopyNativeCurrencyTiles,0x0814186D\n");
void RenderNativeCurrencyDelta(u32,struct NativeCurrencySurface *,u16 *,u16,u16)
    __asm__("SceneTaskDependency_00029F18");
void RenderNativeCurrencyDelta(u32 delta,struct NativeCurrencySurface *surface,
                               u16 *requested_buffer,u16 x,u16 y)
{
    u16 *buffer;
    s32 index;
    u16 *destination;
    {
        register u16 *entry_buffer __asm__("r2") = requested_buffer;
        /* Consume the initialized incoming R2 value after formal normalization. */
        __asm__("" : "+r" (entry_buffer));
        buffer = entry_buffer;
    }
    if (!buffer)
        buffer = (u16 *)0x02003CB0;
    index = (s16)y * 32;
    index += 33;
    index += (s16)x;
    destination = surface->tilemap + index;
    FormatNativeCurrencyTiles(buffer,8,gNativeShopCurrencyRam.currency + delta,0xD000);
    QueueNativeDisplayDefinition(1,115);
    CopyNativeCurrencyTiles(buffer,destination,8);
}
