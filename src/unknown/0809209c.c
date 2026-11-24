typedef unsigned char u8;
typedef unsigned int u32;
struct EffectScanlineContext { u8 samples[324]; u8 channel; };
extern void StageDmaChannelTransfer(u32 channel, u32 source, u32 destination, u32 control);
__asm__(".global StageDmaChannelTransfer\n.thumb_set StageDmaChannelTransfer,0x08000d49");
void StageEffectScanlineTransfer(struct EffectScanlineContext *context)
{
    StageDmaChannelTransfer(context->channel, (u32)context,
                            0x04000052, 0x20400001);
}
