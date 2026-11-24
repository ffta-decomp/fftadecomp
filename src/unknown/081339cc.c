typedef unsigned char u8;
typedef unsigned int u32;
struct EffectStateMask { u8 bits[12]; };
extern const struct EffectStateMask gAlternateEffectStateMasks[];
extern u32 ReadEffectStateChannel(const u8 *mask, int state_index, u32 channel);
asm(".global gAlternateEffectStateMasks\n.set gAlternateEffectStateMasks,0x08527d5c\n.global ReadEffectStateChannel\n.thumb_set ReadEffectStateChannel,0x08131da5");

u8 ReadAlternateEffectStateMask(u32 record_index, int state_index, u8 channel)
{
    return (u8)ReadEffectStateChannel(gAlternateEffectStateMasks[record_index].bits,
                                    state_index, channel);
}
