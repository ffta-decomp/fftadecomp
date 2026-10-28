typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DmaRequest;
struct EffectSurfaceConfig { u8 unaccessed0[20]; u32 destination; };
extern struct EffectSurfaceConfig gEffectSurfaceConfig;
extern struct DmaRequest gEffectClearRequest;
extern void QueueDmaFixedSource16(struct DmaRequest *, u16 value, u32 destination, u16 count);
__asm__(".global gEffectSurfaceConfig\n.set gEffectSurfaceConfig,0x030008b0\n"
        ".global gEffectClearRequest\n.set gEffectClearRequest,0x0200f47c\n"
        ".global QueueDmaFixedSource16\n.thumb_set QueueDmaFixedSource16,0x08000b21");
void QueueEffectSurfaceClear(void)
{
    QueueDmaFixedSource16(&gEffectClearRequest, 0,
                          gEffectSurfaceConfig.destination, 1024);
}
