typedef unsigned char u8;
typedef unsigned int u32;
struct EffectScanlineContext { u8 unaccessed0[324]; u8 channel; };
extern void CancelDmaChannel(u32 channel);
__asm__(".global CancelDmaChannel\n.thumb_set CancelDmaChannel,0x08000d91");
void CancelEffectScanlineTransfer(struct EffectScanlineContext *context)
{
    CancelDmaChannel(context->channel);
}
